/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:12 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/11 13:58:17 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	count;

	i = 0;
	num = 0;
	count = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] && (nptr[i] == 43 || nptr[i] == 45))
	{
		if (nptr[i] == 45)
			count *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num * count);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

long long	ft_strtoll(const char *nptr, char **endptr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
	{
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (endptr != NULL)
		*endptr = (char *)nptr;
	return (result * sign);
}
