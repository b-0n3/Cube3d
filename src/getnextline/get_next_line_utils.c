/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:09:58 by aait-ham          #+#    #+#             */
/*   Updated: 2019/11/06 20:46:17 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*search(int fd, char **rest, int *ret)
{
	char	*tmp;
	char	*ptr;

	ptr = malloc(BUFFER_SIZE + 1);
	while (ft_strchr(*rest, '\n') == NULL)
	{
		*ret = read(fd, ptr, BUFFER_SIZE);
		ptr[*ret] = '\0';
		tmp = ft_strjoin(*rest, ptr);
		free(*rest);
		*rest = ft_strdup(tmp);
		free(tmp);
		if (*ret == 0)
			break ;
	}
	free(ptr);
	return (*rest);
}
