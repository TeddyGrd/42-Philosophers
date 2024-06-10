/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:44:56 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/10 19:45:35 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**parse_single_argument(int *argc, char **argv)
{
	int		count;
	char	**result;

	count = 0;
	result = NULL;
	result = ft_split(argv[1], ' ');
	while (result[count])
		count++;
	*argc = count;
	return (result);
}

char	*combine_arguments(int argc, char **argv)
{
	int			i;
	size_t		total_len;
	char		*joined_args;

	i = 1;
	total_len = 0;
	while (i < argc)
	{
		total_len += ft_strlen(argv[i]) + 1;
		i++;
	}
	joined_args = (char *)malloc(total_len);
	if (!joined_args)
		return (NULL);
	joined_args[0] = '\0';
	i = 1;
	while (i < argc)
	{
		ft_strcat(joined_args, argv[i]);
		if (i < argc - 1)
			ft_strcat(joined_args, " ");
		i++;
	}
	return (joined_args);
}

char	**parse_multiple_arguments(int *argc, char **argv)
{
	int		count;
	char	**result;
	char	*joined_args;

	count = 0;
	result = NULL;
	joined_args = combine_arguments(*argc, argv);
	result = ft_split(joined_args, ' ');
	free(joined_args);
	while (result[count])
		count++;
	*argc = count;
	return (result);
}

char	**parse_arguments(int *argc, char **argv)
{
	char	**result;

	result = NULL;
	if (*argc == 2 && ft_strchr(argv[1], ' '))
		result = parse_single_argument(argc, argv);
	else
		result = parse_multiple_arguments(argc, argv);
	return (result);
}
