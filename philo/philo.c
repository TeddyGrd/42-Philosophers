/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/19 02:00:51 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philosopher p, int last)
{
	if (p.data->check_meal
		&& last == p.data->number_of_philosophers - 1
		&& p.i == p.data->number_of_times_each_philosopher_must_eat)
		return (ft_usleep(300));
	return (0);
}

void	check_thread(t_data *p, t_philosopher *philo)
{
	int	i;

	while (!p->simulation_ready)
		continue ;
	while (!p->simulation_over)
	{
		i = -1;
		while (++i < p->number_of_philosophers)
			if (check_death(&philo[i]) || check_meals(philo[i], i))
				p->simulation_over = 1;
	}
	if (p->check_meal && philo[p->number_of_philosophers - 1].i == p->number_of_times_each_philosopher_must_eat)
	{
		ft_usleep(5 * p->number_of_philosophers);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", p->number_of_times_each_philosopher_must_eat);
		return;
	}
	return;
}

int	init_thread(t_data *p, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < p->number_of_philosophers)
	{
		philo[i].right_fork = philo[(i + 1) % p->number_of_philosophers].left_fork;
					fprintf(stderr,"\n je suis la");

		if (pthread_create(&philo[i].thread, NULL,
				&thread_routine, &philo[i]) == -1)
			return (0);
	}
	i = -1;
	p->simulation_start = current_time_in_ms();
	while (++i < p->number_of_philosophers)
	{
		philo[i].thread_start = p->simulation_start;
		philo[i].last_meal_time = p->simulation_start;
	}
	p->simulation_ready = 1;
	return (0);
}

void	end_thread(t_data *p, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < p->number_of_philosophers)
		pthread_join(philo[i].thread, (void *)&philo[i]);
	pthread_mutex_destroy(p->death);
	pthread_mutex_destroy(p->fork);
	free(p->death);
	free(p->fork);
	free(philo);
}

int	philosophers(t_data *params)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher) * params->number_of_philosophers);
	if (!philo || init_philosophers(params, philo))
		return (EXIT_FAILURE);
	fprintf(stderr,"test");
	if (init_thread(params, philo))
		return (EXIT_FAILURE);
	check_thread(params, philo);
	end_thread(params, philo);
	return (0);
}
