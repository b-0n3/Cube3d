#include "cub3d.h"

extern t_game *game;

void render_player(t_player *this)
{
     t_ray_sp *spray;

   this->wall_rays.foreach(&this->wall_rays, &cast_rays);
    if (game->floor != NULL)
      cast_draw_floor(this);
    this->wall_rays.foreach(&this->wall_rays, &draw_ray);
    while ((spray = (t_ray_sp *)this->light_rays.pull(&this->light_rays) ) != NULL)
    {
        if(spray != NULL)
            draw_sprit(spray);

    }
     while ((spray = (t_ray_sp *)this->sprit_rays.pull(&this->sprit_rays)) != NULL)
     {
        if(spray != NULL)
            draw_sprit(spray);

    }
} 


    
