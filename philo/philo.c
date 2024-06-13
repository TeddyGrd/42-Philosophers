/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/13 17:26:01 by tguerran         ###   ########.fr       */
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

void dead_philo(t_philosopher *philosopher, const char *state)
{
    long long timestamp = current_time_in_ms() - philosopher->data->start_time;
    printf("%lld philo %d %s\n", timestamp, philosopher->id, state);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;
    t_data *data = philosopher->data;

    if (data->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philosopher->left_fork);
        print_state(philosopher, "has taken a fork");
        usleep(data->time_to_die * 1000);
        print_state(philosopher, "died");
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_lock(&data->simulation_mutex);
        data->simulation_running = 0;
        pthread_mutex_unlock(&data->simulation_mutex);
        return NULL;
    }

    while (data->simulation_running)
    {
        pthread_mutex_lock(&data->simulation_mutex);
        if(!data->simulation_running)
        {
            pthread_mutex_unlock(&data->simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&data->simulation_mutex);
        // Penser
        print_state(philosopher, "is thinking");

        // Prendre les fourchettes
        pthread_mutex_lock(philosopher->left_fork);
        print_state(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->right_fork);
        print_state(philosopher, "has taken a fork");

        // Manger
        philosopher->last_meal_time = current_time_in_ms();
        print_state(philosopher, "is eating");
        usleep(data->time_to_eat * 1000);
        philosopher->meals_eaten++;

        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        if (data->number_of_times_each_philosopher_must_eat != -1 &&
            philosopher->meals_eaten >= data->number_of_times_each_philosopher_must_eat)
        {
            pthread_mutex_lock(&data->simulation_mutex);
            data->simulation_running = 0;
            pthread_mutex_unlock(&data->simulation_mutex);
            break;
        }
        // Dormir
        print_state(philosopher, "is sleeping");
        usleep(data->time_to_sleep * 1000);

        // Vérifier s'il meurt de faim
        pthread_mutex_lock(&data->meal_check_mutex);
        if (current_time_in_ms() - philosopher->last_meal_time > data->time_to_die)
        {
            data->simulation_running = 0;
            print_state(philosopher, "died");
			dead_philo(philosopher, "is dead");
            data->death_count++;
            pthread_mutex_unlock(&data->simulation_mutex);
			return NULL ;
        }
        pthread_mutex_unlock(&data->meal_check_mutex);
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
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
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