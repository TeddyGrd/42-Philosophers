/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:24:59 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/24 21:45:45 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)s;
	if ((char)c == '\0')
	{
		i = ft_strlen(str);
		return (&str[i]);
	}
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

long long current_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_state(t_philosopher *philosopher, const char *state)
{
    long long timestamp = current_time_in_ms() - philosopher->data->simulation_start;
    
	pthread_mutex_lock(philosopher->data->death);
	if (philosopher->data->simulation_over)
	{
		pthread_mutex_unlock(philosopher->data->death);
		return ;
	}
	printf("%lld %d %s\n", timestamp, philosopher->id + 1, state);
	pthread_mutex_unlock(philosopher->data->death);
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = current_time_in_ms();
	while ((current_time_in_ms() - start_time) < time)
		usleep(150);
	return (1);
}