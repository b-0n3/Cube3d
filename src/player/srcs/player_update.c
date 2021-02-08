#include "cub3d.h"

extern t_game *game;
extern int nb_rays;

void init_rays(t_player *this)
{
    double ray_angle;
    size_t index;
    t_ray *ray;

    index = 0;
        ray_angle = this->rotaion_angle - (this->fov / 2);
        while (index < this->wall_rays.index)
        {
            ray_angle = normelize_angel(ray_angle);
            ray = (t_ray *) this->wall_rays.get(&this->wall_rays , index);
            if(ray != NULL)
            {
                ray->update(ray , ray_angle, index);
                ray_angle = ray_angle + (this->fov / nb_rays);
            }
            index++;
        }
}

void update_player(t_player *this)
{
    double next_x;
    double next_y;
    double newAngle ;

    newAngle =   this->rotaion_angle + (this->rotation_speed * this->t_dir);
   this->sprit_rays.index = 0;
    next_x =  this->pos->x  + cos(newAngle) *(this->mov_speed * this->w_dir);
     next_y =  this->pos->y  + sin(newAngle) *(this->mov_speed * this->w_dir);
        check_collision(this ,next_x / game->wvalue , next_y / game->hvalue);
        init_rays(this);
      
}