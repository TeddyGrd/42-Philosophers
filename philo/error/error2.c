/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:51:16 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/27 17:24:55 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_parse(char **numbers)
{
	int		i;

	i = 0;
	while (numbers[i])
		i++;
	if (i > 5 || i <= 3)
		return (0);
	if (i >= 5)
	{
		if (ft_atoi(numbers[4]) <= 0)
			return (0);
	}
	return (1);
}

int	f_space(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i] != ' ' || argv[1][i] != '\0')
	{
		if (argv[1][i] == '\0')
			return (1);
		if (argv[1][i] != ' ')
			break ;
		i++;
	}
	return (0);
}
