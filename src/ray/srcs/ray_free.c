#include "cub3d.h"

void free_ray(void *item)
{
    t_ray *ray;
    ray = (t_ray *) item;
    if(ray != NULL)
    {
        if(ray->dir != NULL)
        {
           free(ray->dir);
        }
        free(ray);
    }
    
}

void free_sprite(void *item)
{
    t_sprites *sp = (t_sprites *) item;
    if (sp != NULL)
    {
        free(sp->pos);
        free(sp);
    }
}

void free_wall(void  * item)
{
    t_wall *wall;
    wall = (t_wall *) item;
    if(wall != NULL)
    {
        if (wall->dir != NULL)
            free(wall->dir);
        if(wall->pos != NULL)
            free(wall->pos);
        free(wall);
    }
}

void free_ray_sp(void *item)
{
    t_ray *ray;
    ray  = (t_ray  *) item;
    if(ray != NULL)
    {
        if(ray->dir != NULL)
        {
           free(ray->dir);
           
        }
        if(ray->pos != NULL)
            free(ray->pos);
        free(ray);
    }
}