/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:09:49 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:40:36 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



int			find(char **line, char **rest, int retn)
{
	int		len;
	char	*tmp;
	char	*ptr;

	if (retn == 1)
	{
		tmp = ft_strchr(*rest, '\n');
		len = tmp - *rest;
		*line = ft_substr(*rest, 0, len);
		ptr = ft_strdup(*rest + (len + 1));
		free(*rest);
		*rest = ft_strdup(ptr);
		free(ptr);
	}
	else
	{
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return (retn);
}

int			get_next_line(int fd, char **line)
{
	static char		*rest[255];
	int				ret;

	ret = 0;
	if (fd < 0 || line == NULL || read(fd, NULL, 0) != 0)
		return (-1);
	if (!rest[fd])
		rest[fd] = ft_strdup("");
	search(fd, &rest[fd], &ret);
	if (ft_strchr(rest[fd], '\n'))
		return (find(&line[0], &rest[fd], 1));
	else if (ret == 0)
		return (find(&line[0], &rest[fd], 0));
	return (0);
}
