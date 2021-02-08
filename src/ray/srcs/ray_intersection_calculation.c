#include "cub3d.h"

double calculate_den(t_ray *ray, t_wall wall)
{
    return  ( wall.pos->x - wall.dir->x )
    *( ray->pos->y - ray->dir->y) -
     ( wall.pos->y - wall.dir->y ) 
    * ( ray->pos->x - ray->dir->x );
}


double calculate_t(t_ray *ray , t_wall wall, double den)
{
    return (( wall.pos->x - ray->pos->x) 
    * ( ray->pos->y - ray->dir->y ) 
    - ( wall.pos->y - ray->pos->y ) 
    * ( ray->pos->x - ray->dir->x)) / den;
}

double calculate_u(t_ray *ray , t_wall wall , double den)
{
    return -(( wall.pos->x - wall.dir->x ) 
    * ( wall.pos->y - ray->pos->y ) 
    - ( wall.pos->y - wall.dir->y )
    *( wall.pos->x - ray->pos->x ))
    / den;

}