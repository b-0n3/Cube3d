#include "cub3d.h"
extern t_game *game;
void   render_sprite_texture(double p[] , double wallHei ,t_sp_texture *tex , double dis)
{
      int color;
      t_vector pos;
      int y2;
      float i_step[2];
    
      i_step[0] = 0;
      y2 = p[1]  + wallHei;
      i_step[1]  = tex->height / wallHei;
      new_vector(&pos,  p[0], p[1]);
      while (pos.y < y2)
      {
          color = tex->data[(int)(tex->offset )   + (int) i_step[0]  * (int)tex->width];
          if(color > 0)
            if (!(tex->kind == '5' - 48 && color == tex->data[0]))
            {
                if (tex->kind != '5' - 48 && tex->kind != 10)
                     color = shadow(color , dis);
              image_put_pixel(game->window , p[0] , pos.y, color);
            }
          pos.y += 1;
          i_step[0]  += i_step[1];
      }
}