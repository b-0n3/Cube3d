/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_file_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:32:35 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/13 19:32:40 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		push_bonus_sprites_properties(t_array_list *words)
{
	int i;

	i = 0;
	while (i <= 9)
	{
		words->push(words, ft_itoa(i), sizeof(char *));
		i++;
	}
}

#ifdef BONUS

t_bool		is_empty_or_comment(char *line)
{
	int i;
	int len;

	if (line != NULL)
	{
		len = ft_strlen(line);
		i = 0;
		while (ft_iswhitespace(line[i]))
			i++;
		if (i < len)
			if (line[i] == '#')
				return (TRUE);
		return (i == len && i == 0 ? TRUE : FALSE);
	}
	else
		return (TRUE);
	return (FALSE);
}

t_bool		is_map_character(char ch)
{
	char *arr;

	arr = "012 SNWE";
	if (ch == '\0')
		return (FALSE);
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

#else

t_bool		is_map_character(char ch)
{
	char *arr;

	arr = "0123456789 SNWEs";
	if (ch == '\0')
		return (FALSE);
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

t_bool		is_empty_or_comment(char *line)
{
	int i;
	int len;

	if (line != NULL)
	{
		len = ft_strlen(line);
		i = 0;
		while (ft_iswhitespace(line[i]))
			i++;
		return (i == len && i == 0 ? TRUE : FALSE);
	}
	else
		return (TRUE);
	return (FALSE);
}

#endif
