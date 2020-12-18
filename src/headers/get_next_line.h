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

char		*search(int fd, char **rest, int *ret);
int			get_next_line(int fd, char **line);

int			find(char **line, char **rest, int retn);


#endif
