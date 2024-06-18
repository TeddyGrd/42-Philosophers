/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:08 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/18 15:03:20 by tguerran         ###   ########.fr       */
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

struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			last_meal_time;
	int					meals_eaten;
	t_data				*data;
};


struct s_data
{
	int number_of_philosophers;
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	t_philosopher *philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t eat_mutex;
	pthread_mutex_t	simulation_mutex;
	long long start_time;
	int simulation_running;
	int		death_count;
	int philo_eat;
};

int			check_error(int argc, char *argv[]);
void		init_data(t_data *data, int argc, char **argv);
void		init_philosophers(t_data *data);
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
void		*philosopher_routine(void *arg);


#endif