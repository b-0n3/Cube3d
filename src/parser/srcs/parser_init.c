/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:45:32 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:33 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_parser(t_parser *this, char *filename, t_game *g_p)
{
	new_array_list(&(this->lines), 7, sizeof(char *));
	new_array_list(&(this->tokens), 5, sizeof(t_token *));
	this->parse_file = &parser_parse_file;
	this->get_lines = &get_lines;
	this->get_fd = &get_fd;
	this->do_final = &parser_do_final;
	this->free = &free_parser;
	this->g = g_p;
	this->fd = this->get_fd(filename);
}

void	free_parser(void *th)
{
	t_parser *this;

	this = (t_parser *)th;
	this->lines.free(&this->lines, &free);
	free(this);
}
