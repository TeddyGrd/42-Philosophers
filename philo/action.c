/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:22:02 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 02:04:46 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	someone_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->simulation_over_mutex);
	philo->data->simulation_over = 1;
	pthread_mutex_unlock(&philo->data->simulation_over_mutex);
}

int	check_death(t_philosopher *philosopher)
{
	long long	current_time;

	current_time = current_time_in_ms();
	pthread_mutex_lock(&philosopher->mutex_last_meal);
	if (current_time - philosopher->last_meal_time
		> philosopher->data->time_to_die)
	{
		pthread_mutex_unlock(&philosopher->mutex_last_meal);
		print_state(philosopher, "died");
		someone_died(philosopher);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->mutex_last_meal);
	return (0);
}

void	take_forks(t_philosopher *philosopher)
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

void	ft_sleep_and_think(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->mutex_state);
	print_state(philosopher, "is sleeping");
	pthread_mutex_unlock(&philosopher->mutex_state);
	ft_usleep(philosopher->data->time_to_sleep);
	pthread_mutex_lock(&philosopher->mutex_state);
	print_state(philosopher, "is thinking");
	pthread_mutex_unlock(&philosopher->mutex_state);
}

void	ft_eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
	pthread_mutex_lock(&philosopher->mutex_last_meal);
	philosopher->last_meal_time = current_time_in_ms();
	pthread_mutex_unlock(&philosopher->mutex_last_meal);
	pthread_mutex_lock(&philosopher->mutex_state);
	print_state(philosopher, "is eating");
	pthread_mutex_unlock(&philosopher->mutex_state);
	ft_usleep(philosopher->data->time_to_eat);
	pthread_mutex_lock(&philosopher->mutex_iter);
	philosopher->iter++;
	if (philosopher->data->number_of_times_each_philosopher_must_eat != -1
		&& philosopher->iter
		>= philosopher->data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->data->simulation_mutex);
		philosopher->data->check_meal++;
		pthread_mutex_unlock(&philosopher->data->simulation_mutex);
	}
	pthread_mutex_unlock(&philosopher->mutex_iter);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}
