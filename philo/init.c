/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:33:09 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/13 16:44:39 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	i = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->death_count = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (argc == 6)
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
        data->number_of_times_each_philosopher_must_eat = -1;
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->meal_check_mutex, NULL);
	pthread_mutex_init(&data->simulation_mutex,NULL);
    data->simulation_running = 1;
    data->start_time = current_time_in_ms();
}

void	init_philosophers(t_data *data)
{
	int i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	while(i < data->number_of_philosophers)
	{
		data->philosophers[i].id = i +1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i +1) % data->number_of_philosophers];
		data->philosophers[i].last_meal_time = current_time_in_ms();
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->forks[i],NULL);
		i++;
	}
}