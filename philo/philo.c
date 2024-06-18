/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/18 15:04:04 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_state(t_philosopher *philosopher, const char *state)
{
    long long timestamp = current_time_in_ms() - philosopher->data->start_time;
    printf("%lld %d %s\n", timestamp, philosopher->id, state);
}

void ft_usleep(int duration) {
    usleep(duration * 1000);
}

int is_dead(t_philosopher *philo, int state) {
    pthread_mutex_lock(&philo->data->simulation_mutex);
    if (state == 1) {
        philo->data->simulation_running = 0;
    }
    int dead = !philo->data->simulation_running;
    pthread_mutex_unlock(&philo->data->simulation_mutex);
    return dead;
}

void *check_death(void *phi) {
    t_philosopher *philo = (t_philosopher *)phi;
    ft_usleep(philo->data->time_to_die + 1);
    pthread_mutex_lock(&philo->data->eat_mutex);
    if (!is_dead(philo, 0) && current_time_in_ms() - philo->last_meal_time >= (long long)philo->data->time_to_die) {
        print_state(philo, "died");
        is_dead(philo, 1);
    }
    pthread_mutex_unlock(&philo->data->eat_mutex);
    return NULL;
}

void take_fork(t_philosopher *philo) {
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    if (philo->data->number_of_philosophers == 1) {
        ft_usleep(philo->data->time_to_die * 2);
        return;
    }
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
}

void philo_eat(t_philosopher *philo) {
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->data->eat_mutex);
    philo->last_meal_time = current_time_in_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->eat_mutex);
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    print_state(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
    print_state(philo, "is thinking");
}

void *philo_life(void *phi) {
    t_philosopher *philo = (t_philosopher *)phi;
    pthread_t t;

    if (philo->id % 2 == 0) {
        ft_usleep(philo->data->time_to_eat / 10);
    }

    while (!is_dead(philo, 0)) {
        pthread_create(&t, NULL, check_death, phi);
        take_fork(philo);
        philo_eat(philo);
        pthread_detach(t);
        if (philo->meals_eaten == philo->data->number_of_times_each_philosopher_must_eat) {
            pthread_mutex_lock(&philo->data->simulation_mutex);
            philo->data->philo_eat++;
            if (philo->data->philo_eat == philo->data->number_of_philosophers) {
                pthread_mutex_unlock(&philo->data->simulation_mutex);
                is_dead(philo, 2);
            }
            pthread_mutex_unlock(&philo->data->simulation_mutex);
            return NULL;
        }
    }
    return NULL;
}
void start_simulation(t_data *data)
{
    int	i;
	i = 0;
    while (i < data->number_of_philosophers)
    {
		if(data->death_count > 0)
			return;
        pthread_create(&data->philosophers[i].thread, NULL, philo_life, &data->philosophers[i]);
		if(data->death_count > 0)
			return;
		i++;
	}
	i = 0;

    while (i < data->number_of_philosophers)
    {
		if(data->death_count > 0)
			return;
        pthread_join(data->philosophers[i].thread, NULL);
		if(data->death_count > 0)
			return;
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	if (argc < 5)
		return (1);
	if (check_error(argc, argv) == 1)
		return (1);
	i = 0;
	init_data(&data, argc, argv);
	init_philosophers(&data);
	start_simulation(&data);
    if (data.death_count >= 1)
    {
        printf(" %d  mort\n",data.death_count);
        return 1;
    }
	while(i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	free(data.forks);
	free(data.philosophers);
    return (0);
}