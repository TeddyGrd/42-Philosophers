/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:22:02 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/19 01:38:40 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	someone_died(t_philosopher *philosopher)
{
	print_state(philosopher, "died");
	philosopher->data->simulation_over = 1;
	philosopher->dead = 1;
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	return (1);
}

int	check_death(t_philosopher *philosopher)
{
	long int	now;

	pthread_mutex_lock(philosopher->data->death);
	now = current_time_in_ms() - philosopher->last_meal_time;
	if (now >= philosopher->data->time_to_die)
	{
		pthread_mutex_unlock(philosopher->data->death);
		return (someone_died(philosopher));
	}
	pthread_mutex_unlock(philosopher->data->death);
	return (0);
}

void	ft_sleep_and_think(t_philosopher *philosopher)
{
	ft_usleep(philosopher->data->time_to_sleep);
	print_state(philosopher, "are sleeping");
	print_state(philosopher, "is thinking");
}

void	ft_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_state(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->right_fork);
	print_state(philosopher, "has taken a fork");
	philosopher->last_meal_time = current_time_in_ms();
	ft_usleep(philosopher->data->time_to_eat);
	print_state(philosopher, "is eating");
	philosopher->i++;
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	*thread_routine(void *job)
{
	t_philosopher	*p;

	p = (t_philosopher *)job;
	while (!p->data->simulation_ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->data->time_to_eat * 0.9 + 1);
	while (!p->data->simulation_over)
	{
		ft_eat(p);
		ft_sleep_and_think(p);
	}
	return (NULL);
}