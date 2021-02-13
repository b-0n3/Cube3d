/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:38:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:39:02 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_errors(void *item)
{
	char	*str;

	str = (char *)item;
	if (str != NULL)
	{
		write(2, "error:\n", 8);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
}

void	game_exit(struct s_game *this, char *err_msg)
{
	int ret;

	ret = 0;
	if (err_msg != NULL)
	{
		perror(err_msg);
		free(err_msg);
		ret = 1;
	}
	else if (this->errors.index > 0)
	{
		this->errors.foreach(&this->errors, &print_errors);
		ret = 1;
	}
	this->free(this);
	exit(ret);
}
