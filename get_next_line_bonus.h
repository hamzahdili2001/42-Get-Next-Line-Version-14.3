/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:35:57 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/28 15:33:14 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# define FD_MAX 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30720
# endif

size_t	ft_strlen(const char *s);
size_t	l_count(char *buffer);
char	*ft_substr(char *s, size_t start, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
#endif
