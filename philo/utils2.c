/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:55:56 by tguerran          #+#    #+#             */
/*   Updated: 2024/06/10 21:23:23 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = ft_strlen(s);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s [i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	char		*nstr;
	size_t		i;
	size_t		x;

	x = ft_strlen(s);
	i = start;
	if (s == NULL || x < start)
		return (ft_strdup(""));
	if (start + len < x)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((x - start + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	nstr = str;
	while (i < (start + len) && *(s + i))
		*nstr++ = *(s + i++);
	*nstr = '\0';
	return (str);
}

static void	ft_oskour(char **tab, char const *s, char sep)
{
	char		**tab1;
	char const	*tmp;

	tmp = s;
	tab1 = tab;
	while (*tmp)
	{
		while (*s == sep)
			s++;
		tmp = s;
		while (*tmp && *tmp != sep)
			tmp++;
		if (*tmp == sep || tmp > s)
		{
			*tab1 = ft_substr(s, 0, tmp - s);
			s = tmp;
			tab1++;
		}
	}
	*tab1 = NULL;
}

static int	ft_worlen(char const *s, char sep)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			i++;
		while (*s && *s != sep)
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_worlen(s, c);
	str = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	ft_oskour(str, s, c);
	return (str);
}
