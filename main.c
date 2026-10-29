/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:04:06 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/29 12:17:15 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int	callnextline(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	printf("%s", line);
	free(line);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (1);
	while (!callnextline(fd))
		;
	close(fd);
	return (0);
}
