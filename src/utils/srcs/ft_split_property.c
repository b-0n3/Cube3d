/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_property.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:52:18 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:19 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_array_list	*ft_split_property(char *line)
{
	t_array_list	*words;
	int				i;
	int				j;

	words = (t_array_list *)malloc(sizeof(t_array_list));
	new_array_list(words, 2, sizeof(char *));
	j = 0;
	if (line != NULL)
	{
		while (ft_iswhitespace(line[j]))
			j++;
		i = j;
		while (!ft_iswhitespace(line[i]))
			i++;
		words->push(words, ft_substr(line, j, i - j), sizeof(char *));
		while (ft_iswhitespace(line[i]) && line[i] != '\0')
			i++;
		j = ft_strlen(line);
		while (j > i && ft_iswhitespace(line[j - 1]))
			j--;
		if (j > i)
			words->push(words, ft_substr(line, i, j - i), sizeof(char*));
		return (words);
	}
	return (words);
}
