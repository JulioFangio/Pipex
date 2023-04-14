/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:35:31 by juduval           #+#    #+#             */
/*   Updated: 2023/04/14 15:04:27 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	if ((s1[i] - s2[i]) < -127)
		return ((s1[i] - s2[i]) * -1);
	return (s1[i] - s2[i]);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ns;
	size_t	tmp;

	tmp = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (ft_calloc(1, 1));
	if ((tmp / nmemb) != size)
		return (NULL);
	ns = malloc(nmemb * size);
	if (!(ns))
		return (NULL);
	ft_bzero(ns, nmemb * size);
	return (ns);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = '\0';
		i++;
	}
}

char	*ft_strdup(const char *s)
{
	int		size;
	char	*copy;

	size = ft_strlen(s);
	copy = malloc(size + 1 * sizeof(char));
	if (!(s))
		return (NULL);
	size = 0;
	while (s[size])
	{
		copy[size] = s[size];
		size++;
	}
	copy[size] = '\0';
	return (copy);
}