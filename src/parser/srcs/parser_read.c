/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:45:54 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:56 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_lines(t_parser *this)
{
	char *line;
	int result;

	if (this->fd > -1)
	{
		while ((result = get_next_line(this->fd, &line)) > 0)
		{
			if (this->lines.push(&(this->lines), ft_strdup(line), sizeof(line)) != TRUE) 
				this->lines.free(&(this->lines), &free);
			free(line);
		}
		if (this->lines.push(&(this->lines),(void *) ft_strdup(line), sizeof(line)) != TRUE) 
			this->lines.free(&(this->lines), &free);
		free(line);
	}
	else
		put_error(this->g, ft_strdup("invalid file"));
	close(this->fd);
}

int get_fd(char *filename)
{
	int fd = -1;
	if (filename != NULL)
		fd = open(filename , O_RDONLY);
	return fd;
}
