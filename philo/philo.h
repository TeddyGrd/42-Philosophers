/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:08 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/07 17:24:26 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_philosopher
{
	int		id;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philosophers;

typedef struct s_data
{
	int number_of_philosophers;
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	t_philosophers *philosophers;
	pthread_mutex_t	*forks;
}	t_data;

int		check_error(int argc, char *argv[]);
void	init_data(t_data *data, int argc, char **argv);
void	init_philosophers(t_data *data);
int		ft_atoi(const char *nptr);

#endif