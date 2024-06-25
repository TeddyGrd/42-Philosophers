/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:48:32 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/25 14:28:46 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5)
		return (1);
	if (check_error(argc, argv) == 1)
		return (1);
	init_data(&data, argc, argv);
	if (philosophers(&data))
		return (1);
	return (0);
}
