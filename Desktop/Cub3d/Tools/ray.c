#include "Cube3d.h"
extern t_game *game;

t_ray *new_ray(t_vector *pos, double angle)
{
    t_ray *ray;
    ray = (t_ray *)malloc(sizeof (t_ray));
    if (ray != NULL)
    {
        ray->angle = angle;
        ray->pos = pos;
        ray->kind = -1;
        ray->dir = pos->get_dir_angle(pos, angle);
        ray->render = &render_ray;
        ray->cast = &cast_ray;
    }

    return ray;
}

void    cast_ray(void *ray)
{

}

void    render_ray(t_ray *this)
{
    this->pos->to_string(this->pos);

    this->dir->to_string(this->dir);
    printf("\nnew one __________________________________________ \n");
   // if ((this->angle > M_PI_2 && this->angle < 3 *M_PI_2 ))
   //         draw_line(game->window ,this->pos, this->dir, 0x2c786c);
 //   else
        draw_line(game->window ,this->dir,this->pos, 0x2c786c);
    
}