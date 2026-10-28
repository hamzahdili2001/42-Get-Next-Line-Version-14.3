/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:09:40 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 15:41:14 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static size_t	guard(char *s, size_t start, size_t len)
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
	size_t	count;
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	count = guard(s, start, len);
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	char	*ptr;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	ptr = joined;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (joined);
}
*/

size_t	l_count(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	return (len);
}
