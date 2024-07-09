/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:00:56 by tguerran          #+#    #+#             */
/*   Updated: 2024/07/09 02:15:26 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_until_simulation_ready(t_philosopher *philo)
{
	int	simulation_ready;

	while (1)
	{
		pthread_mutex_lock(&philo->data->simulation_mutex);
		simulation_ready = philo->data->simulation_ready;
		pthread_mutex_unlock(&philo->data->simulation_mutex);
		if (simulation_ready)
			break ;
		ft_usleep(1);
	}
}

void	handle_single_philosopher(t_philosopher *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		print_state(philo, "died");
		pthread_mutex_lock(&philo->data->simulation_over_mutex);
		philo->data->simulation_over = 1;
		pthread_mutex_unlock(&philo->data->simulation_over_mutex);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	initial_thread_setup(t_philosopher *philo)
{
	wait_until_simulation_ready(philo);
	handle_single_philosopher(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat * 0.9 + 1);
}

void	main_thread_routine(t_philosopher *philo)
{
	int	simulation_over;

	while (1)
	{
		pthread_mutex_lock(&philo->data->simulation_over_mutex);
		simulation_over = philo->data->simulation_over;
		pthread_mutex_unlock(&philo->data->simulation_over_mutex);
		if (simulation_over)
			break ;
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->simulation_mutex);
		if (philo->data->number_of_times_each_philosopher_must_eat != -1
			&& philo->data->check_meal >= philo->data->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo->data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->simulation_mutex);
		ft_sleep_and_think(philo);
	}
}

void	*thread_routine(void *t)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)t;
	initial_thread_setup(philo);
	if (philo->data->number_of_philosophers == 1)
		return (NULL);
	main_thread_routine(philo);
	return (NULL);
}
