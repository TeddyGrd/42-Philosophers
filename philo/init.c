/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:33:09 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 00:16:30 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex(t_data *data)
{
	int i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork)
		return (1);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->fork[i], NULL);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (1);
	pthread_mutex_init(data->death, NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);
	pthread_mutex_init(&data->simulation_over_mutex, NULL);  // Initialisation du mutex
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		mutex;
	char	**numbers;

	numbers = parse_arguments(&argc, argv);
	mutex = -1;
	data->number_of_philosophers = ft_atoi(numbers[0]);
	data->time_to_die = ft_atoi(numbers[1]);
	data->time_to_eat = ft_atoi(numbers[2]);
	data->time_to_sleep = ft_atoi(numbers[3]);
	data->simulation_start = 0;
	pthread_mutex_init(&data->simulation_mutex, NULL);
	data->simulation_ready = 0;
	data->simulation_over = 0;
	data->check_meal = 0;
	if (argc == 5 || numbers[4])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(numbers[4]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	mutex = init_mutex(data);
	free_split(numbers);
	return (mutex);
}

int init_philosophers(t_data *data, t_philosopher *philosophers)
{
    int i;

    i = -1;
    while (++i < data->number_of_philosophers)
    {
        philosophers[i].id = i;
        philosophers[i].data = data;
        philosophers[i].left_fork = &data->fork[i];
        philosophers[i].right_fork = &data->fork[(i + 1) % data->number_of_philosophers];
        pthread_mutex_init(&philosophers[i].mutex_iter, NULL);
        pthread_mutex_init(&philosophers[i].mutex_last_meal, NULL);
        pthread_mutex_init(&philosophers[i].mutex_state, NULL);  // Initialisation du mutex
    }
    return (0);
}

