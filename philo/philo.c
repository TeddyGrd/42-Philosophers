/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:36:23 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/07 17:22:47 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philosophers *philosopher = (t_philosophers *)arg;

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
        usleep(1000);  // Simuler le temps de manger

        // Reposer les fourchettes
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        // Dormir
        printf("%d is sleeping\n", philosopher->id);
        usleep(1000);  // Simuler le temps de dormir
    }

    return NULL;
}

void start_simulation(t_data *data)
{
    for (int i = 0; i < data->number_of_philosophers; i++)
    {
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
    }

    for (int i = 0; i < data->number_of_philosophers; i++)
    {
        pthread_join(data->philosophers[i].thread, NULL);
    }
}


int main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	if (argc < 5)
		return (1);
	//if (check_error(argc, argv) == 1)
	//	return (1);
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