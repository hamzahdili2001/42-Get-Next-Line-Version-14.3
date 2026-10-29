/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:46:02 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/29 11:12:14 by hhdili           ###   ########.fr       */
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

char	*grow(char *s, size_t len, size_t *cap)
{
	char	*new;
	size_t	i;

	*cap = 2 * len + BUFFER_SIZE + 1;
	new = malloc(*cap);
	if (!new)
		return (free(s), NULL);
	i = 0;
	while (i <= len)
	{
		new[i] = s[i];
		i++;
	}
	free(s);
	return (new);
}
