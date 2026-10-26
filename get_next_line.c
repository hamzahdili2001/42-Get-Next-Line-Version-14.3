/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 09:11:31 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/26 15:05:38 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*fill_save(int fd, char *saved)
{
	char	*buf;
	char	*tmp;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(saved), NULL);
	n = 1;
	while (n > 0 && saved[l_count(saved)] != '\n')
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (free(buf), free(saved), NULL);
		buf[n] = '\0';
		tmp = ft_strjoin(saved, buf);
		free(saved);
		saved = tmp;
		if (!saved)
			break ;
	}
	free(buf);
	return (saved);
}

static char	*extract_line(char *saved)
{
	size_t	len;

	len = l_count(saved);
	if (saved[len] == '\n')
		len++;
	return (ft_substr(saved, 0, len));
}

static char	*trim_saved(char *saved)
{
	size_t	start;
	char	*rest;

	start = l_count(saved);
	if (saved[start] == '\n')
		start++;
	rest = ft_substr(saved, start, ft_strlen(saved));
	free(saved);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_substr("", 0, 0);
	if (!saved)
		return (NULL);
	saved = fill_save(fd, saved);
	if (!*saved)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	line = extract_line(saved);
	saved = trim_saved(saved);
	return (line);
}
