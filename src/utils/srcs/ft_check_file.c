/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:51:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:02 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool ft_check_file(char *file_name,char *extension)
{
	int i;
	int len;
	int fd;
	int len2;

	i = 0;
	if (file_name == NULL || extension == NULL)
		return FALSE;
	fd = open(file_name , O_RDONLY);
	if (fd < 0)
		return FALSE;
	close(fd);
	len = ft_strlen(extension) - 1;
	len2 = ft_strlen(file_name) - 1;
	if ((len + 1) > len2 || len < 0 || len2 < 0)
		return FALSE;
	while(len >= 0)
	{
		if (extension[len] != file_name[len2])
			return (FALSE);
		len2--;
		len--;
	}
	return (TRUE);
}
