/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:53:26 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:53:27 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

t_texture		*new_texture(char *link)
{
	t_texture	*tex;
	void		*ptr;

	tex = (t_texture *)malloc(sizeof(t_texture));
	if (tex != NULL)
	{
		tex->offset = 0;
		ptr = mlx_xpm_file_to_image(g_game->window.mlx,
				link, &tex->width, &tex->height);
		tex->img.img_ptr = ptr;
		if (tex->img.img_ptr == NULL)
			g_game->errors.push(&g_game->errors, ft_strdup("invalid texture"),
					sizeof(char *));
		tex->data = (int *)mlx_get_data_addr(tex->img.img_ptr, &(tex->img.bpp)
				, &tex->img.size_line, &(tex->img.endian));
	}
	return (tex);
}

t_sp_texture	*get_sp_tex(int kind)
{
	t_sp_texture	*tex;
	t_sp_texture	*ntex;
	size_t			i;

	tex = NULL;
	ntex = NULL;
	i = 0;
	while (i < g_game->allocated_sp_tex.index)
	{
		ntex = g_game->allocated_sp_tex.get(&g_game->allocated_sp_tex, i);
		if (ntex != NULL)
			if (ntex->kind == kind)
			{
				tex = ntex;
				break ;
			}
		i++;
	}
	return (tex);
}

t_sp_texture	*new_sp_texture(char *link, int kind)
{
	t_sp_texture *tex;

	tex = NULL;
	if (link != NULL)
	{
		tex = (t_sp_texture *)malloc(sizeof(t_sp_texture));
		if (tex != NULL)
		{
			tex->offset = 0;
			tex->img.img_ptr = mlx_xpm_file_to_image(g_game->window.mlx, link,
					&tex->width, &tex->height);
			tex->data = (int *)mlx_get_data_addr(tex->img.img_ptr, &tex->img.bpp
					, &tex->img.size_line, &tex->img.endian);
			tex->kind = kind;
		}
	}
	return (tex);
}
