/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:10:09 by aait-ham          #+#    #+#             */
/*   Updated: 2019/11/06 20:42:26 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFFER_SIZE 1024
// char		*ft_substr(char *s, unsigned int start, size_t len);
// char		*ft_strjoin(char *s1, char *s2);
// char		*ft_strchr(const char *s, int c);
char		*search(int fd, char **rest, int *ret);
int			get_next_line(int fd, char **line);
// char		*ft_strcpy(char *dest, char *src);
// char		*ft_strdup(char *src);
int			find(char **line, char **rest, int retn);
// size_t		ft_strlen(const char *s);

#endif
