/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:55:16 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/14 15:55:18 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_token(void *item)
{
	t_token *this;

	this = (t_token *)item;
	if (this != NULL)
	{
		if (this->token != NULL)
			free(this->token);
		if (this->values.arr != NULL)
			this->values.free(&this->values, &free);
		free(this);
	}
}
