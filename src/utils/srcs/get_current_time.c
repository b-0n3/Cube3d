/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:52:24 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:28 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_long		get_current_time(void)
{
	struct timeval cur;

	gettimeofday(&cur, NULL);
	return ((t_long)cur.tv_sec * 1000000 + (t_long)cur.tv_usec);
}
