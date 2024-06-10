/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:11:25 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/07 15:14:24 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(int argc, char *argv[])
{
	int		i;
	char	**numbers;

	i = 0;
	if (f_space(argv) == 1)
		return (1);
	numbers = parse_arguments(&argc, argv);
	while (i < argc)
	{
		if (number_error(numbers, i) == 0 || double_error(numbers, i) == 0)
		{
			ft_printf("Error\n");
			free_split(numbers);
			return (1);
		}
		i++;
	}
	free_split(numbers);
	return (0);
}