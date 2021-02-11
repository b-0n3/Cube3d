/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:42:15 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:42:23 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINE_H
#define FT_LINE_H
#include "vector.h"

typedef struct s_line {
	t_vector *pos;
	t_vector *dir;
}   t_line;

#endif
