#include "Cube3d.h"

t_window windo;

void draw_rec(t_window wi ,t_vector pos , int size , int color)
{
    int x = pos.x ;
    int x2 = pos.x + size;
    int y1 = pos.y ;
    int y2 = pos.y + size ;

while (y1 < y2)
  {
    int x1 = x;
  while ( x1 < x2)
  { 
   
      mlx_pixel_put(wi.mlx , wi.win, x1, y1 ,color);
    x1++;
     
  }
  y1++;
  }
}

void	line(int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	xinc;
	float	yinc;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	i = -1;
	while (++i <= steps)
	{
	  mlx_pixel_put(windo.mlx , windo.win, (int) x0 ,(int) y0, color);
		x0 += xinc;
		y0 += yinc;
	}
}

void  draw_line(t_window wi ,t_vector *pos , t_vector *dir , int color)
{
  windo = wi;
  
  line(pos->x, pos->y , dir->x, dir->y,color);
// int dx =  abs (dir->x - pos->x), sx = pos->x < dir->x ? 1 : -1;
//   int dy = -abs (dir->y - pos->y), sy = pos->y < dir->y ? 1 : -1; 
//   int err = dx + dy, e2; /* error value e_xy */
//  int x0 = pos->x;
//  int y0 = pos->y;
//   for (;;){  /* loop */
//     mlx_pixel_put(wi.mlx , wi.win, (int) x0 ,(int) y0, color);
//     if (x0 == dir->x && y0 == dir->y) break;
//     e2 = 2 * err;
//     if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
//     if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
//   }
  //    if (pos->x < dir->x)
  //       ft_swap( (void **)&pos,(void **) &dir);    
  //    int m_new = 2 * (dir->y - pos->y); 
  //    int slope_error_new = m_new - (dir->x - pos->x); 
  //    int x = pos->x;
  //    int y = pos->y;

  //   while ( x <= dir->x) 
  //   { 
  //        mlx_pixel_put(wi.mlx , wi.win, (int) x ,(int) y, color);
  //     slope_error_new += m_new; 
  //      if (slope_error_new >= 0) 
  //      { 
  //         y++; 
  //         slope_error_new  -= 2 * (dir->x - pos->x); 
  //      } 
  //      x++;
  //  } 
  //  ft_swap( (void **)&pos,(void **) &dir);
}
