/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:32:25 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/13 19:32:29 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_parser *g_parser;

t_bool		is_map_line(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (FALSE);
	if (line[0] == '\0' || ft_is_empty(line))
		return (FALSE);
	while (ft_iswhitespace(line[i]))
		i++;
	while (is_map_character(line[i]))
		i++;
	if (line[i] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool		map_ended(char *line, t_bool *var)
{
	if (var == NULL)
		*var = FALSE;
	if (map_created() && !is_map_line(line))
		*var = TRUE;
	return (*var);
}

t_bool		map_created(void)
{
	t_token *token;

	token = get_token_by_key(g_parser, "MAP");
	return (token == NULL ? FALSE : TRUE);
}

t_bool		create_map(char *line)
{
	t_token *token;

	if (line == NULL)
		return (FALSE);
	if (map_created())
		token = get_token_by_key(g_parser, "MAP");
	else
	{
		token = (t_token *)malloc(sizeof(t_token ));
		new_empty_token(token, ft_strdup("MAP"));
		if (token != NULL)
			g_parser->tokens.push(&(g_parser->tokens),
					token, sizeof(t_token *));
	}
	if (token == NULL)
		return (FALSE);
	token_push_value(token, line);
	return (TRUE);
}
