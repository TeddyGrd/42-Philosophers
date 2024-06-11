/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:11:25 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/11 17:11:55 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_an_int(const char *argv)
{
	long long	value;
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(argv);
	if (len > 11)
		return (1);
	while (i < len)
	{
		if (i == 0 && (argv[i] == '-' || argv[i] == '+'))
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	value = ft_atoi(argv);
	if (value > INT_MAX || value < INT_MIN)
		return (1);
	return (0);
}

long long	ft_atoi_long(const char *str)
{
	return (ft_strtoll(str, NULL));
}

int	number_error(char *argv[], int i)
{
	long long	x;
	char		*str;

	str = argv[i];
	if (is_an_int(str))
		return (0);
	x = ft_strtoll(str, NULL);
	if (x > INT_MAX || x < INT_MIN)
		return (0);
	return (1);
}


int error_test(char *argv[])
{
	if (ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}

int	check_error(int argc, char *argv[])
{
	int		i;
	char	**numbers;

	i = 0;
	if (f_space(argv) == 1)
		return (1);
	if(error_test(argv) == 1)
		return (1);
	numbers = parse_arguments(&argc, argv);
	while (i < argc)
	{
		if (number_error(numbers, i) == 0)
		{
			printf("Error\n");
			free_split(numbers);
			return (1);
		}
		i++;
	}
	free_split(numbers);
	return (0);
}