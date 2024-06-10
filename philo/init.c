/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:33:09 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/10 19:40:31 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int		i;
	(void)argc;
	i = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
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
		data->philosophers[i].data = data;
		i++;
	}
}