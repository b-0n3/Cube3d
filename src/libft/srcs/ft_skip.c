/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:54:08 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/13 17:54:12 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip(char *line, int index, char ch)
{
	if (line == NULL || index < 0)
		return (index < 0 ? 0 : index);
	while (line[index] == ch)
		index++;
	return (index);
}
