#include "cub3d.h"
extern int nb_rays;

t_vector *get_sprite_inter(t_vector *pos, t_vector *dir , t_vector *c_pos, double rad)
{
        double baX = dir->x - pos->x;
        double baY = dir->y - pos->y;
        double caX = c_pos->x - pos->x;
        double caY = c_pos->y - pos->y;

        double a = baX * baX + baY * baY;
        double bBy2 = baX * caX + baY * caY;
        double c = caX * caX + caY * caY - rad * rad;

        double pBy2 = bBy2 / a;
        double q = c / a;

        double disc = pBy2 * pBy2 - q;

        if (disc < 0) {
           return NULL;
        }
        double tmpSqrt = sqrt(disc);
        double abScalingFactor1 = -pBy2 + tmpSqrt;
        double abScalingFactor2 = -pBy2 - tmpSqrt;
        if (abScalingFactor1 <= 0)
        {
         t_vector *p1 = new_vector_pointer(pos->x - baX * abScalingFactor1,
         pos->y - baY * abScalingFactor1);
            return p1;
        }
        return NULL;
}


void    cast_sprite(t_vector *pos, t_sprites *sp, t_ray_sp **ray_sp , double r_len, double angle, int index)
{
    t_vector *in;
    t_vector sub;
    double splen ;
    t_vector *dir;
   dir =  new_vector_pointer(pos->x + r_len * cos(angle) , pos->y + r_len *sin(angle));
   
    in = get_sprite_inter(pos, dir , sp->pos, sp->rad);
   free(dir);
    if(in != NULL)
    {
        new_vector(&sub , pos->x - in->x, pos->y - in->y);
        splen = sub.length(&sub);
        if(splen < r_len)
        {
            if(*ray_sp == NULL)
            {
                *ray_sp = new_sp_ray(pos, in , angle , index, sp);
            }
            else   if(splen < (*ray_sp)->length(*ray_sp))
            {
                (*ray_sp)->update(*ray_sp , in, sp);
            }
            
        }
      
                free(in);
    }
    free(pos);
}

double get_angle (double x ,double y)
{
    double res;
    if (y < 0 || x < 0)
        return 0;
    res = x / y;
    return atan(res);
}

t_sprites *new_sprite(t_vector *pos, double rad, int kind)
{
    double angle;

    t_sprites *sp = (t_sprites *) malloc (sizeof(t_sprites));
    sp->pos = pos;
    sp->rad = rad;
    sp->kind = kind;
    sp->free = &free_sprite;
    sp->d_a = get_angle(sp->pos->x , sp->pos->y + rad);
    sp->u_a = get_angle (sp->pos->x , sp->pos->y - rad);
    
    angle  = sp->u_a - sp->d_a;
    sp->a_p_r = angle / nb_rays;
    return sp;
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