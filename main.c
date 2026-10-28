/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:04:06 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 11:41:07 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	callnextline(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	printf("%s", line);
	free(line);
	return (0);
}

int	main(void)
{
	int	fd;
	int	fd2;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 == -1)
		return (1);
	callnextline(fd);
	callnextline(fd2);
	callnextline(fd2);
	return (0);
}
