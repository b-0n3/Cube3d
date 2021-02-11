/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:52:08 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:10 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "util.h"
# include "game.h"

void    put_error(t_game *g_p, char *message)
{
	g_p->errors.push(&g_p->errors , message,
			sizeof (char *));
}
