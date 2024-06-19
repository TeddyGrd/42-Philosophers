/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:33:09 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/19 02:11:02 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int i;

	i = -1;
	data->death = 0;
	data->fork = 0;
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork)
		return (1);
	if(pthread_mutex_init(data->death,NULL) == -1)
		return (1);
	while (++i < data->number_of_philosophers)
	{
		if(pthread_mutex_init(&data->fork[i],NULL) == -1)
			return(1);
	}
	return (0);
}

int	init_data(t_data *data,int argc, char **argv)
{
	int mutex;

	mutex = -1;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->simulation_start = 0;
	data->simulation_ready = 0;
	data->simulation_over = 0;
	data->check_meal = 0;
	if (argc == 6)
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
        data->number_of_times_each_philosopher_must_eat = -2;
	mutex = init_mutex(data);
	return (mutex);
}

int	init_philosophers(t_data *data, t_philosopher *philosophers)
{
	int i;

	i = -1 ;
	while(i < data->number_of_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].dead = 0;
		philosophers[i].i = 0;
		philosophers[i].thread_start = 0;
		philosophers[i].last_meal_time = 0;
		philosophers[i].data = data;
		philosophers[i].left_fork = &data->fork[i];
		philosophers[i].right_fork = 0;
		i++;
	}
	return (0);
}