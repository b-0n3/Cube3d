/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:09 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:15 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parser	*g_parser;

#ifdef BONUS

t_bool		is_wall_character(char ch)
{
	char *arr;

	arr = " 12s";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

t_bool		is_map_s_or_end(char ch)
{
	char *arr;

	arr = "12s";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

#else

t_bool		is_map_s_or_end(char ch)
{
	char *arr;

	arr = "1";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

t_bool		is_wall_character(char ch)
{
	char *arr;

	arr = " 1";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

#endif

t_bool		check_borders(t_array_list lines)
{
	return (check_border_e(lines)
			&& check_border_s(lines)
			&& check_border_i(lines, 0));
}

void		verify_map(t_parser *this)
{
	t_token			*token;
	t_array_list	lines;

	token = get_token_by_key(this, "MAP");
	if (token == NULL || token->values.arr == NULL
		|| token->values.index <= 0)
		put_error(this->g, ft_strdup("no map!"));
	else
	{
		g_parser = this;
		lines = token->values;
		if (!(check_borders(lines) && check_inside(lines, 0, 0)))
			put_error(this->g, ft_strdup("invalid map"));
	}
}
