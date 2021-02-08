#include "cub3d.h"
double      ray_len(t_ray *ray)
{
    t_vector sub;

    new_vector(&sub, ray->pos->x - ray->dir->x , ray->pos->y - ray->dir->y);
    
    return (sub.length(&sub));
}

double      ray_sp_len(t_ray_sp *ray)
{
    t_vector sub;

    new_vector(&sub, ray->pos->x - ray->dir->x , ray->pos->y - ray->dir->y);
    return (sub.length(&sub));
}
