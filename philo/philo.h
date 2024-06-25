/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:08 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/25 01:18:31 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_philosopher t_philosopher;
typedef struct s_data t_data;


struct s_data
{
	int number_of_philosophers;
	int simulation_ready;
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int check_meal;
	int simulation_over;
	long int simulation_start;
	pthread_mutex_t	*fork;
	pthread_mutex_t *death;
};

struct s_philosopher
{
	int					id;
	int					dead;
	int					iter;
	long int			last_meal_time;
	long int			thread_start;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
};

int			check_error(int argc, char *argv[]);
int			init_data(t_data *data, int argc, char **argv);
int			init_philosophers(t_data *data, t_philosopher *philosophers);
int			ft_atoi(const char *nptr);
long long 	current_time_in_ms(void);
int			check_error(int argc, char *argv[]);
int			f_space(char **argv);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
long long	ft_strtoll(const char *nptr, char **endptr);
char		**ft_split(char const *s, char c);
void		free_split(char **numbers);
char		*ft_strchr(const char *s, int c);
char		*ft_strcat(char *dest, const char *src);
char		**parse_arguments(int *argc, char **argv);
void		*thread_routine(void *job);
void		print_state(t_philosopher *philosopher, const char *state);
int			ft_usleep(long int time);
int			check_death(t_philosopher *philosopher);
int			init_thread(t_data *data, t_philosopher *philosopher);
int			init_mutex(t_data *data);
int			philosophers(t_data *data);

#endif