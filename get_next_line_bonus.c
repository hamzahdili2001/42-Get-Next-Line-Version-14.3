/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:34:21 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 15:44:57 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_save(int fd, char *saved)
{
	char	*buf;
	char	*tmp;
	size_t	len;
	size_t	cap;
	ssize_t	n;

	len = ft_strlen(saved);
	cap = len + 1;
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
		if (len + n + 1 > cap)
		{
			cap = (len + n + 1) * 2;
			tmp = realloc(saved, cap);
			if (!tmp)
				return (free(buf), free(saved), NULL);
			saved = tmp;
		}
		ft_memcpy(saved + len, buf, n);
		len += n;
		saved[len] = '\0';
		/*
		tmp = ft_strjoin(saved, buf);
		free(saved);
		saved = tmp;
		if (!saved)
			break ;
		*/
	}
	free(buf);
	return (saved);
}
/*
static char	*fill_save(int fd, char *saved)
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
*/
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
	saved[fd] = trim_saved(saved[fd]);
	return (line);
}
