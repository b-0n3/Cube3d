/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:51:35 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:51:48 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
#define FT_UTILS_H
#include "array_list.h"
#include "libft.h"
#include "game.h"
#include <sys/time.h>

t_array_list *ft_split_property(char *line);
void put_error(t_game *g_p, char *message);
int rgb_to_int(int r, int g, int b);
long long  get_current_time();
t_bool ft_check_file(char *file_name,char *extension);
#endif
