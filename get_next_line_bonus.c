/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:34:21 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/29 17:39:40 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_save(int fd, char *saved)
{
	size_t	len;
	size_t	cap;
	ssize_t	n;

	if (saved[l_count(saved)] == '\n')
		return (saved);
	len = ft_strlen(saved);
	cap = len + 1;
	n = 1;
	while (n > 0)
	{
		if (cap - len - 1 < BUFFER_SIZE)
			saved = grow(saved, len, &cap);
		if (!saved)
			return (NULL);
		n = read(fd, saved + len, BUFFER_SIZE);
		if (n < 0)
			return (free(saved), NULL);
		saved[len + n] = '\0';
		if (saved[len + l_count(saved + len)] == '\n')
			break ;
		len += n;
	}
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
	static char	*saved[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved[fd])
		saved[fd] = ft_substr("", 0, 0);
	if (!saved[fd])
		return (NULL);
	saved[fd] = fill_save(fd, saved[fd]);
	if (!saved[fd] || !*saved[fd])
	{
		free(saved[fd]);
		saved[fd] = NULL;
		return (NULL);
	}
	line = extract_line(saved[fd]);
	if (!line)
		return (NULL);
	saved[fd] = trim_saved(saved[fd]);
	return (line);
}
