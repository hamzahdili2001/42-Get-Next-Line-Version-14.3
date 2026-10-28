/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:04:06 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 12:12:50 by hhdili           ###   ########.fr       */
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

	fd = open("big_line_no_nl", O_RDONLY);
	if (fd == -1)
		return (1);
	callnextline(fd);
	return (0);
}
