/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:22:02 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 00:48:19 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void someone_died(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->simulation_over_mutex);
    philo->data->simulation_over = 1;
    pthread_mutex_unlock(&philo->data->simulation_over_mutex);
}


int check_death(t_philosopher *philosopher)
{
    long long current_time = current_time_in_ms();

    pthread_mutex_lock(&philosopher->mutex_last_meal);  // Verrouillage du mutex dernier repas
    if (current_time - philosopher->last_meal_time > philosopher->data->time_to_die)
    {
        pthread_mutex_unlock(&philosopher->mutex_last_meal);  // Déverrouillage du mutex dernier repas
        print_state(philosopher, "died");
        someone_died(philosopher);
        return 1;
    }
    pthread_mutex_unlock(&philosopher->mutex_last_meal);  // Déverrouillage du mutex dernier repas
    return 0;
}

void take_forks(t_philosopher *philosopher)
{
    if (philosopher->id % 2 == 0)
    {
        pthread_mutex_lock(philosopher->left_fork);
        print_state(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->right_fork);
        print_state(philosopher, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philosopher->right_fork);
        print_state(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->left_fork);
        print_state(philosopher, "has taken a fork");
    }
}

void ft_sleep_and_think(t_philosopher *philosopher)
{
    pthread_mutex_lock(&philosopher->mutex_state);  // Verrouillage du mutex d'état
    print_state(philosopher, "is sleeping");
    pthread_mutex_unlock(&philosopher->mutex_state);  // Déverrouillage du mutex d'état

    ft_usleep(philosopher->data->time_to_sleep);

    pthread_mutex_lock(&philosopher->mutex_state);  // Verrouillage du mutex d'état
    print_state(philosopher, "is thinking");
    pthread_mutex_unlock(&philosopher->mutex_state);  // Déverrouillage du mutex d'état
}


void ft_eat(t_philosopher *philosopher)
{
    take_forks(philosopher);

    pthread_mutex_lock(&philosopher->mutex_last_meal);
    philosopher->last_meal_time = current_time_in_ms();
    pthread_mutex_unlock(&philosopher->mutex_last_meal);

    pthread_mutex_lock(&philosopher->mutex_state);  // Verrouillage du mutex d'état
    print_state(philosopher, "is eating");
    pthread_mutex_unlock(&philosopher->mutex_state);  // Déverrouillage du mutex d'état

    ft_usleep(philosopher->data->time_to_eat);

    pthread_mutex_lock(&philosopher->mutex_iter);
    philosopher->iter++;
    if (philosopher->data->number_of_times_each_philosopher_must_eat != -1 &&
        philosopher->iter >= philosopher->data->number_of_times_each_philosopher_must_eat)
    {
        pthread_mutex_lock(&philosopher->data->simulation_mutex);
        philosopher->data->check_meal++;
        pthread_mutex_unlock(&philosopher->data->simulation_mutex);
    }
    pthread_mutex_unlock(&philosopher->mutex_iter);

    pthread_mutex_unlock(philosopher->right_fork);
    pthread_mutex_unlock(philosopher->left_fork);
}




void *thread_routine(void *t)
{
    t_philosopher *philo = (t_philosopher *)t;
    int simulation_ready;
    int simulation_over;

    // Attendre que la simulation soit prête
    while (1)
    {
        pthread_mutex_lock(&philo->data->simulation_mutex);
        simulation_ready = philo->data->simulation_ready;
        pthread_mutex_unlock(&philo->data->simulation_mutex);
        if (simulation_ready)
            break;
        ft_usleep(1);  // Petite pause pour éviter la boucle infinie
    }

    // Gérer le cas d'un seul philosophe
    if (philo->data->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        ft_usleep(philo->data->time_to_die);
        pthread_mutex_lock(&philo->data->simulation_over_mutex);
        philo->data->simulation_over = 1;
        pthread_mutex_unlock(&philo->data->simulation_over_mutex);
        print_state(philo, "died");
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }

    // Pause pour les philosophes avec un ID pair
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat * 0.9 + 1);

    // Boucle principale
    while (1)
    {
        pthread_mutex_lock(&philo->data->simulation_over_mutex);
        simulation_over = philo->data->simulation_over;
        pthread_mutex_unlock(&philo->data->simulation_over_mutex);

        if (simulation_over)
            break;

        ft_eat(philo);

        pthread_mutex_lock(&philo->data->simulation_mutex);
        if (philo->data->number_of_times_each_philosopher_must_eat != -1 &&
            philo->data->check_meal >= philo->data->number_of_philosophers)
        {
            pthread_mutex_unlock(&philo->data->simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->simulation_mutex);

        ft_sleep_and_think(philo);
    }
    return NULL;
}
