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

long long  get_current_time()
{
	struct timeval cur;

	gettimeofday(&cur, NULL);
	return ((long long ) cur.tv_sec * 1000000 + (long long ) cur.tv_usec); 
}
