#include "Cube3d.h"
extern t_game *game;


double      ray_len(t_ray *ray)
{
    t_vector sub;

    new_vector(&sub, ray->pos->x - ray->dir->x , ray->pos->y - ray->dir->y);
    return (sub.length(&sub));
}

t_ray *new_ray(t_vector *pos, double angle)
{
    t_ray *ray;
    ray = (t_ray *)malloc(sizeof (t_ray));
    if (ray != NULL)
    {
        
        ray->pos = pos;
      
       ray->update = &update_ray;
        ray->render = &render_ray;
        ray->cast = &cast_ray;
        ray->length = &ray_len;
        ray->update(ray , angle);
    }

    return ray;
}


void    get_intesection_wall(t_ray *ray, t_wall wall)
{
    double newx;
    double newy;
    double new_len;
    float t = 0;
    float u = 0;
    t_vector sub;
    double x3= ray->pos->x;
    double x4 = ray->dir->x;

    double x1 = wall.pos->x;
    double x2 = wall.dir->x;
   
    double y3 = ray->pos->y;
    double y4 = ray->dir->y;
    
    double y1 = wall.pos->y;
    double y2 = wall.dir->y;

    new_vector(&sub , ray->pos->x, ray->pos->y);
    double den = (x1 - x2)*(y3 - y4) - (y1 -y2) * (x3-x4);
   if (den != 0)
   {
    t = ((x1 -x3) *(y3- y4 ) - (y1 - y3) *( x3 - x4))/ den;
    u = -((x1 -x2) * (y1 -y3) - (y1 - y2)*(x1 - x3))/den;

   if ((t < 1.0f && t > 0.0f) && u > 0)
   {
   
        newx =( x1 + t * (x2 -x1)) ;
        newy =( y1 + t *(y2 -y1)) ;
    sub.sub(&sub,new_vector_pointer(newx ,newy));
    new_len = sub.length(&sub);
        if (ray->kind == -1)
        {
            ray->dir->x = newx;
            ray->dir->y = newy;
            ray->kind = 1;
        }
        else
        {
            if(new_len < ray->length(ray))
            {
                ray->dir->x = newx;
                ray->dir->y = newy;
            }
        }
        
   }
}
}

/*

11111111111111111111
11111000000000000001
11111000001111111111
100000000001
1000N0000001
111100001111111111111
1000000000000000001
11111111111111111111

*/


void    cast_ray(void *r)
{
    int index;
    t_wall wall;
    index = 0;
    t_ray *ray = (t_ray *) r;
    while (index < game->walls.index)
    {
        wall = *((t_wall *)game->walls.get(&game->walls, index));
        get_intesection_wall(ray, wall);
        index++;
    }
}



void    render_ray(t_ray *this)
{
    this->cast(this);
   //this->pos->to_string(this->pos);

    //this->dir->to_string(this->dir);
    t_vector sub;

    new_vector(&sub,this->dir->x - this->pos->x   ,this->dir->y - this->pos->y );
  // printf("\nnew one __________________________________________ \n");
   // if ((this->angle > M_PI_2 && this->angle < 3 *M_PI_2 ))
            //draw_line(game->window ,this->pos, this->dir, 0x2c786c);
   //else
       // draw_line(game->window ,this->dir,this->pos, 0x2c786c);
       if(this->kind == 1)
        ft_line(this->pos->x, this->pos->y, floor(sub.length(&sub)),this->angle);
    //ft_line(this->dir->x, this->dir->y, 1, this->angle);
    
}
void update_ray(t_ray *this, double angle)
{
    this->angle = angle;
    this->dir = this->pos->get_dir_angle(this->pos, this->angle);
    this->kind = -1;
    this->len = this->length(this);
}