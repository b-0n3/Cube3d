#include "Cube3d.h"
extern t_game *game;
int coli;

double      ray_len(t_ray *ray)
{
    t_vector sub;

    new_vector(&sub, ray->pos->x - ray->dir->x , ray->pos->y - ray->dir->y);
    return (sub.length(&sub));
}

t_ray *new_ray(t_vector *pos, double angle, int i)
{
    t_ray *ray;
    ray = (t_ray *)malloc(sizeof (t_ray));
    if (ray != NULL)
    {
        
        ray->pos = pos;
      
       ray->update = &update_ray;
        ray->render = &render_ray;
        ray->cast = &cast_ray;
        ray->free = &free_ray;
        ray->length = &ray_len;
        ray->dir = NULL;
        ray->update(ray , angle, i);
        ray->coli = 0;
    }

    return ray;
}

t_ray *new_ray_with_dir(t_vector *pos, t_vector *dir,  double angle, int i)
{
    t_ray *ray;
    ray = (t_ray *)malloc(sizeof (t_ray));
    if (ray != NULL)
    {
        
        ray->pos = new_vector_pointer(pos->x, pos->y);

       ray->update = &update_ray;
        ray->render = &render_ray;
        ray->cast = &cast_ray;
        ray->length = &ray_len;
        ray->free = &free_ray;
        ray->dir = new_vector_pointer(dir->x, dir->y);
        ray->angle = angle;
        ray->index = i;
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
      
      if(u >0 && u < 0.4)
         ray->coli  = 1;
        newx =( x1 + t * (x2 -x1)) ;
        newy =( y1 + t *(y2 -y1)) ;
 double    nx = newx - sub.x;
double  ny = newy - sub.y;
    sub.x = nx;
    sub.y = ny;
    new_len = sub.length(&sub);
        if (ray->kind == -1)
        {
            ray->dir->x = newx;
            ray->dir->y = newy;
            ray->kind = wall.kind;
        }
        else
        {
            if(new_len < ray->length(ray))
            {
                ray->kind = wall.kind;
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

    if(ray->index != -10)
    {
        index = 0;
        t_ray   *sp = NULL;

        while (index < game->sprites.index)
        {
            t_sprites *spp = game->sprites.get(&game->sprites, index);
            cast_sprite(new_vector_pointer(ray->pos->x, ray->pos->y), spp, &sp , ray->length(ray),ray->angle , ray->index);
            index++;
        }
        if(sp != NULL)
            game->player.sprit_rays.push(&(game->player.sprit_rays), sp , sizeof(t_ray));
    }
 }




void    render_ray(t_ray *this)
{
    this->cast(this);
    double dispro;
    double wallHei;
    double correctdis;
   //this->pos->to_string(this->pos);

    //this->dir->to_string(this->dir);
    //t_vector sub;

   // new_vector(&sub,this->pos->x - this->dir->x   ,this->pos->y - this->dir->y );
  // printf("\nnew one __________________________________________ \n");
   // if ((this->angle > M_PI_2 && this->angle < 3 *M_PI_2 ))
            //draw_line(game->window ,this->pos, this->dir, 0x2c786c);
   //else
       // draw_line(game->window ,this->dir,this->pos, 0x2c786c);
     double start;
     double end;
     double xsize;
     double ysize;
     double color;
        if(this->kind >= 0)
       {
           correctdis = this->length(this) * cos(this->angle - game->player.rotaion_angle);
           dispro = (game->width /2) * tan(game->player.fov /2);
           wallHei = (game->wvalue / correctdis) * dispro;
           //printf("dispro : %f     walhei : %f", dispro, wallHei);
           start = this->index ;
           end = ((game->heigth / 2) - (wallHei /2));
           ysize = wallHei;
           xsize = 1;
            if (this->kind == 0 )
            color = shadow(0xf8b400 , correctdis);
            else  if (this->kind == 1)
            color = shadow(0xfaf5e4, correctdis) ;
            else  if (this->kind == 2)
            color = shadow(0x2c786c, correctdis) ;
            else             
               color = shadow( 0xeb4559, correctdis) ;
            rec(start,end, xsize, ysize ,color);

            rec(start, end + wallHei , xsize,  game->heigth - end, 0x231903);
             rec(start,0 , xsize,  game->heigth - end- wallHei, 0x363636);
        }
       // ft_line(this->pos->x, this->pos->y , floor(sub.length(&sub)),this->angle, color);
    //ft_line(this->dir->x, this->dir->y, 1, this->angle);
    
}
void update_ray(t_ray *this, double angle, int i)
{
    this->index = i;
    this->angle = angle;
    if(this->dir != NULL)
        free(this->dir);
    this->dir = this->pos->get_dir_angle(this->pos, this->angle);
    this->kind = -1;
    this->len = this->length(this);
}

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
