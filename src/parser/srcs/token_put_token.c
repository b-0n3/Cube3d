/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_put_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:32:48 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/13 19:32:52 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_parser *g_parser;

void		put_token(t_parser *p, t_array_list word)
{
	t_token *token;

	if (get_token_by_key(p, (char *)word.get(&word, 0)) == NULL)
	{
		token = (t_token *)malloc(sizeof(t_token));
		new_token(token, word);
		p->tokens.push(&(p->tokens), token, sizeof(t_token *));
	}
	else
		put_error(p->g, ft_strdup("diplicate property "));
}

static  void	parse_token_sp(char *line)
{
	t_array_list	*word;

	word = ft_split_property(line);
	if (word != NULL && word->index > 1)
	{
		if (!check_properties(word->get(word, 0)))
			put_error(g_parser->g,
					ft_strjoin("invalid line :\n", line));
		else
			put_token(g_parser, *word);
	}
	else
		put_error(g_parser->g, ft_strjoin("invalid line :\n", line));
	word->free(word, &free);
	free(word);
}

void		parse_token(void *item)
{
	char			*line;
	static t_bool	var;

	if (item != NULL && g_parser != NULL)
	{
		line = (char *)item;
		if (!map_ended(line, &var) && is_map_line(line))
			create_map(line);
		else if (!map_created() && !is_empty_or_comment(line))
			parse_token_sp(line);
		else if (((map_created() || map_ended(line, &var))
					&& !ft_is_empty(line)))
			put_error(g_parser->g,
					ft_strjoin("propeties after map line :\n", line));
	}
}
