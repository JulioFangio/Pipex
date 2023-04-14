/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:12:21 by juduval           #+#    #+#             */
/*   Updated: 2023/04/14 15:04:24 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l_s1;
	size_t	l_s2;
	char	*ns;

	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	ns = malloc(((l_s1 + l_s2) + 1) * sizeof(char));
	if (!(ns))
		return (NULL);
	ft_strcpy(ns, s1);
	ft_strcpy(ns + l_s1, s2);
	return (ns);
}