/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:46:02 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 10:46:02 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	l_count(char *buffer)
{
	size_t	size;

	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	return (size);
}

static size_t	guard(size_t len, char *s, size_t start)
{
	size_t	count;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		count = 0;
	else if (len > slen - start)
		count = slen - start;
	else
		count = len;
	return (count);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*sub;
	size_t	count;
	size_t	i;

	count = guard(len, s, start);
	sub = malloc(count + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	s1len;
	size_t	s2len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}
