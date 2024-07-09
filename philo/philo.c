/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 01:46:37 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philo[i].right_fork = philo[(i + 1)
			% data->number_of_philosophers].left_fork;
		if (pthread_create(&philo[i].thread, NULL,
				&thread_routine, &philo[i]) == -1)
			return (0);
	}
	i = -1;
	data->simulation_start = current_time_in_ms();
	while (++i < data->number_of_philosophers)
	{
		philo[i].thread_start = data->simulation_start;
		philo[i].last_meal_time = data->simulation_start;
	}
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_ready = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (0);
}

void	end_thread(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].mutex_iter);
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
		pthread_mutex_destroy(&philo[i].mutex_state);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(&data->simulation_mutex);
	pthread_mutex_destroy(&data->simulation_over_mutex);
	free(data->death);
	free(data->fork);
	free(philo);
}

int	philosophers(t_data *data)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!philo || init_philosophers(data, philo))
		return (1);
	if (init_thread(data, philo))
		return (1);
	check_thread(data, philo);
	end_thread(data, philo);
	return (0);
}
