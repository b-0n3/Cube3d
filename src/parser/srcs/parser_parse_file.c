/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:45:41 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:48 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parser		*g_parser;
t_array_list	*g_keywords;

void		parser_parse_file(t_parser *this)
{
	if (this != NULL && this->lines.arr != NULL && this->tokens.arr != NULL)
	{
		g_parser = this;
		g_keywords = (t_array_list *)malloc(sizeof(t_array_list));
		new_array_list(g_keywords, 7, sizeof(char *));
		init_properties(g_keywords);
		this->lines.foreach(&(this->lines), &parse_token);
		verify_map(g_parser);
		g_keywords->free(g_keywords, &free);
		free(g_keywords);
	}
}

#ifdef BONUS

void	init_properties(t_array_list *words)
{
	if (words != NULL && words->arr != NULL)
	{
		words->push(words, ft_strdup("R"), sizeof(char *));
		words->push(words, ft_strdup("NO"), sizeof(char *));
		words->push(words, ft_strdup("SO"), sizeof(char *));
		words->push(words, ft_strdup("WE"), sizeof(char *));
		words->push(words, ft_strdup("EA"), sizeof(char *));
		words->push(words, ft_strdup("F"), sizeof(char *));
		words->push(words, ft_strdup("C"), sizeof(char *));
		words->push(words, ft_strdup("MAP"), sizeof(char *));
		push_bonus_sprites_properties(words);
	}
}

#else

void		init_properties(t_array_list *words)
{
	if (words != NULL && words->arr != NULL)
	{
		words->push(words, ft_strdup("R"), sizeof(char *));
		words->push(words, ft_strdup("NO"), sizeof(char *));
		words->push(words, ft_strdup("SO"), sizeof(char *));
		words->push(words, ft_strdup("WE"), sizeof(char *));
		words->push(words, ft_strdup("EA"), sizeof(char *));
		words->push(words, ft_strdup("F"), sizeof(char *));
		words->push(words, ft_strdup("C"), sizeof(char *));
		words->push(words, ft_strdup("MAP"), sizeof(char *));
		words->push(words, ft_strdup("S"), sizeof(char *));
	}
}

#endif

t_bool		ft_is_empty(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (line != NULL)
	{
		len = ft_strlen(line);
		while (ft_iswhitespace(line[i]) && line[i] != '\0')
			i++;
	}
	return (len == i ? TRUE : FALSE);
}

t_bool		check_properties(char *token)
{
	size_t	index;
	char	*key;
	int		len1;
	int		len2;

	if (token != NULL)
	{
		index = 0;
		while (index < g_keywords->index)
		{
			key = (char *)g_keywords->get(g_keywords, index);
			len1 = ft_strlen(key);
			len2 = ft_strlen(token);
			if (key != NULL && ft_strncmp(token,
			key, (len1 > len2 ? len1 : len2)) == 0)
				return (TRUE);
			index++;
		}
	}
	return (FALSE);
}
