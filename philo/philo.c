/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/10 21:40:17 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;

    while (1)
    {
        // Penser
        printf("%d is thinking\n", philosopher->id);

        // Prendre les fourchettes
        pthread_mutex_lock(philosopher->left_fork);
        printf("%d has taken a fork\n", philosopher->id);
        pthread_mutex_lock(philosopher->right_fork);
        printf("%d has taken a fork\n", philosopher->id);

        // Manger
        printf("%d is eating\n", philosopher->id);
        usleep(philosopher->data->time_to_eat);

        // Reposer les fourchettes
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        // Dormir
        printf("%d is sleeping\n", philosopher->id);
        usleep(philosopher->data->time_to_sleep);

        if(current_time_in_ms() - philosopher->last_meal_time > philosopher->data->time_to_die)
        {
            printf("%d died \n",philosopher->id);
            break;
        }
    }

    return NULL;
}

void start_simulation(t_data *data)
{
    int	i;

	i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
		i++;
	}
	i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}


int main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	if (argc < 5)
		return (1);
	if (check_error(argc, argv) == 1)
		return (1);
	i = 0;
	init_data(&data, argc, argv);
	init_philosophers(&data);
	start_simulation(&data);
	while(i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	free(data.forks);
	free(data.philosophers);
    return (0);
}