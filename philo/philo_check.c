/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:44:00 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 01:52:08 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_over(t_data *data)
{
	pthread_mutex_lock(&data->simulation_over_mutex);
	if (data->simulation_over)
	{
		pthread_mutex_unlock(&data->simulation_over_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->simulation_over_mutex);
	return (0);
}

int	check_all_meals(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->simulation_mutex);
	pthread_mutex_lock(&data->simulation_over_mutex);
	if (data->number_of_times_each_philosopher_must_eat != -1
		&& data->check_meal >= data->number_of_philosophers)
	{
		data->simulation_over = 1;
		printf("All philosophers have eaten %d times\n",
			data->number_of_times_each_philosopher_must_eat);
		result = 1;
	}
	pthread_mutex_unlock(&data->simulation_over_mutex);
	pthread_mutex_unlock(&data->simulation_mutex);
	return (result);
}

int	check_any_death(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (check_death(&philo[i]))
		{
			pthread_mutex_lock(data->death);
			pthread_mutex_lock(&data->simulation_over_mutex);
			data->simulation_over = 1;
			pthread_mutex_unlock(&data->simulation_over_mutex);
			pthread_mutex_unlock(data->death);
			return (1);
		}
	}
	return (0);
}

void	check_thread(t_data *data, t_philosopher *philo)
{
	while (!data->simulation_ready)
		continue ;
	while (1)
	{
		if (check_simulation_over(data))
			break ;
		if (check_all_meals(data))
			break ;
		if (check_any_death(data, philo))
			break ;
		ft_usleep(1);
	}
}
