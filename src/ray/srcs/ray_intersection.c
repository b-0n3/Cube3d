#include "cub3d.h"
extern t_game *game;


void put_ray_pos(t_ray *ray, t_wall wall, double new_len , double *newpos)
{
    
    if (ray->kind == -1)
        {
            ray->dir->x = newpos[0];
            ray->dir->y = newpos[1];
            ray->kind = wall.kind;
        }
        else
            if(new_len < ray->length(ray))
            {
                ray->kind = wall.kind;
                ray->dir->x = newpos[0];
                ray->dir->y = newpos[1];
            }
}

void put_wall_pos(t_ray  * ray , t_wall wall, double t)
{
    double newpos[2];
    double new_len;
    t_vector sub;
 

    new_vector(&sub , ray->pos->x, ray->pos->y);
     newpos[0] =( wall.pos->x + t * (wall.dir->x - wall.pos->x)) ;
    newpos[1]=( wall.pos->y + t *(wall.dir->y - wall.pos->y)) ;
    sub.x  = newpos[0] - sub.x;
    sub.y = newpos[1] - sub.y;
    new_len = sub.length(&sub);
    put_ray_pos(ray, wall, new_len, newpos);
}

void    get_intesection_wall(t_ray *ray, t_wall wall)
{
    float t;
    float u;
    double den;

    den  = calculate_den(ray , wall);
   if (den != 0)
   {
    t = calculate_t(ray, wall, den);
    u = calculate_u(ray , wall ,den);
   if ((t < 1.0f && t > 0.0f) && u > 0)
   {
      
      if(u >0 && u < 0.4)
         ray->coli  = 1;
        put_wall_pos(ray ,wall ,t);
   }
}
}

