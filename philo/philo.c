/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/25 14:29:05 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philosopher philo, int last)
{
	if (last == philo.data->number_of_philosophers - 1
		&& philo.iter == philo.data->number_of_times_each_philosopher_must_eat)
		return (ft_usleep(300));
	return (0);
}

void	check_thread(t_data *data, t_philosopher *philo)
{
	int	i;

	while (!data->simulation_ready)
		continue ;
	while (!data->simulation_over)
	{
		i = -1;
		while (++i < data->number_of_philosophers)
			if (check_death(&philo[i]) || check_meals(philo[i], i) != 0)
				data->simulation_over = 1;
	}
	if (philo[data->number_of_philosophers - 1].iter
		== data->number_of_times_each_philosopher_must_eat)
	{
		ft_usleep(5 * data->number_of_philosophers);
		printf("						\n");
		printf("All philosophers have eaten %d times \n",
			data->number_of_times_each_philosopher_must_eat);
		return ;
	}
	return ;
}

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
	data->simulation_ready = 1;
	return (0);
}

void	end_thread(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(philo[i].thread, (void *)&philo[i]);
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->fork);
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
