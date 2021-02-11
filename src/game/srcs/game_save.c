/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:39:44 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:39:47 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_header(unsigned char **header, int imagesize,t_game *this)
{
	u_int16_t bitcount;
	u_int32_t bisize;
	u_int32_t bfoffbits;
	u_int32_t filesize;
	u_int16_t biplanes;

	biplanes = 1;
	filesize = 54 + imagesize;
	bfoffbits = 54;
	bisize = 40;
	bitcount = 24;
	memset(*header, 0, 54);
	ft_memcpy(*header, "BM", 2);
	ft_memcpy(*header + 2, &filesize, 4);
	ft_memcpy(*header + 10, &bfoffbits, 4);
	ft_memcpy(*header + 14, &bisize, 4);
	ft_memcpy(*header + 18, &this->width, 4);
	ft_memcpy(*header + 22, &this->heigth, 4);
	ft_memcpy(*header + 26, &biplanes, 2);
	ft_memcpy(*header + 28, &bitcount, 2);
	ft_memcpy(*header + 34, &imagesize, 4);
}

void	fill_buf(unsigned char **buf, int width_in_bytes, t_game *this)
{
	int row;
	int col;
	int color;
	int i;
	int	j;

	row = this->heigth;
	i = 0;
	while (--row > 0)
	{
		col = 0;
		j = 0;
		while (++col < this->width)
		{
			color = ((int *)this->window.img->img_data)[(row * this->width) + col];
			(*buf)[i * width_in_bytes + j * 3 + 0] = color & 0xFF;
			(*buf)[i * width_in_bytes + j * 3 + 1] = (color & 0xFF00) >> 8;
			(*buf)[i * width_in_bytes + j * 3 + 2] = (color & 0xFF0000) >> 16;
			j++;
		}
		i++;
	}
}
void	save_first_frame_in_bmp_file(t_game *this)
{
	int				width_in_bytes;
	u_int32_t		imagesize;
	unsigned char	*buf;
	int				fd;
	unsigned char	*header;

	width_in_bytes = ((this->width * 24 + 31) / 32) * 4;
	imagesize = width_in_bytes * this->heigth;
	header = (unsigned char *)malloc(imagesize);
	fill_header(&header, imagesize, this);
	buf = malloc(imagesize);
	fd = open("img.bmp", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	fill_buf(&buf, width_in_bytes, this);
	write(fd, header, 54);
	write(fd, buf, imagesize);
	close(fd);
}
void save_game(t_game *this)
{
	save_first_frame_in_bmp_file(this);
	this->exit(this, NULL);
}
