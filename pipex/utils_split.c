/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:35:31 by juduval           #+#    #+#             */
/*   Updated: 2023/05/23 13:43:18 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	ft_isseparator(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static	int	ft_countwords(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isseparator(str[i], sep))
			i++;
		else
		{
			count++;
			while (str[i] != sep && str[i])
				i++;
		}
	}
	return (count);
}

static	char	*ft_strdupbis(const char *s, char sep)
{
	int		size;
	char	*copy;

	size = 0;
	while (s[size] != sep && s[size])
		size++;
	copy = malloc(size + 2 * sizeof(char));
	if (!(copy))
		return (NULL);
	size = 0;
	while (s[size] && s[size] != sep)
	{
		copy[size] = s[size];
		size++;
	}
	copy[size] = '/';
	copy[size + 1] = '\0';
	return (copy);
}

char	**ft_free(char **s, int j)
{
	while (j >= 0)
	{
		free(s[j]);
		j--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ns;

	i = 0;
	j = 0;
	ns = ft_calloc((ft_countwords(s, c) + 1), sizeof(char *));
	if (!(ns))
		return (0);
	if (ft_countwords(s, c) == 0)
		return (ns);
	while (s[i])
	{
		if (ft_isseparator(s[i], c))
			i++;
		else
		{
			ns[j] = ft_strdupbis(s + i, c);
			if (!(ns[j]))
				return (ft_free(ns, j));
			i += ft_strlen(ns[j++]) - 1;
		}
	}
	return (ns);
}
