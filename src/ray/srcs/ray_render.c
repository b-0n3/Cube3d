#include "cub3d.h"

extern t_game *game;

void draw_ray(void *item)
{
    t_ray *ray;

    ray = (t_ray *) item;
    if(ray != NULL)
        ray->render(ray);
   
}
void render_wall_normal(t_ray *this, double end , double wall_hei, double correctdis)
{
     t_texture *tex;

      tex = pick_texture(this->kind);
       if(tex != NULL)
      {
      tex->offset = (this->kind == 0 || this->kind == 2)  ? fmod(this->dir->x ,game->wvalue)
                        :fmod(this->dir->y ,game->wvalue);
      tex->offset = (tex->offset / game->wvalue) * tex->width;
      render_wall_texture((double []){this->index , end }, wall_hei , tex ,correctdis);
      }
}
void render_wall_pic(t_ray *this,double end , double wall_hei, double correctdis)
{
  t_sp_texture *text;
     char *line;
      int y;
      int x;

    y = ((this->dir->y /  game->hvalue) - 1) +((this->kind == 2 || this->kind == 0)? 1 :0);
    x = ((this->dir->x /  game->hvalue) -1 )+ (this->kind == 1 ? 1 : 0);
    line = (char *)game->parser->lines.get(
            &game->parser->lines,  y);
    text = NULL;
    if (line != NULL && line[x] == '2')
      text = get_sp_tex(2);
    if(text != NULL)
            {
                text->offset =( (this->kind == 0 || this->kind == 2)  ?
                 fmod(this->dir->x ,game->wvalue)
                        :fmod(this->dir->y ,game->wvalue) )
                 +  game->hvalue / text->width;
                text->offset = fmod(text->offset ,game->hvalue);
                text->offset = fabs(text->offset);
               render_sprite_texture((double[]){this->index, end} , wall_hei ,
                text , correctdis);
    }
    else
      render_wall_normal(this,end ,wall_hei,correctdis);
}


void    render_ray(t_ray *this)
{
    double dispro;
    double wall_hei;
    double correctdis;
     double end;

        if(this->kind >= 0)
       {
           correctdis = this->length(this) * cos(this->angle - game->player.rotaion_angle);
           dispro = (game->width / 4) * tan(game->player.fov);
           wall_hei = (game->wvalue / correctdis) * dispro;
           end = ((game->heigth / 2) - (wall_hei / 2));
            if (game->floor == NULL) 
              rec(this->index, end + wall_hei + game->player.offset, 1,  
              game->heigth /2 - game->player.offset,
               game->color[4]);  
          rec(this->index,0 , 1,  game->heigth - end - wall_hei + game->player.offset, game->color[5]);
            end += game->player.offset;
            #ifdef BONUS
                render_wall_pic(this,end ,wall_hei,correctdis);
            #else
                render_wall_normal(this,end ,wall_hei,correctdis);
            #endif
      }
}