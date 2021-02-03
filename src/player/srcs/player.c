#include "cub3d.h"

extern t_game *game;
extern int nb_rays;


double  normelize_angel(double angle)
{
    angle = fmod(angle , 2 * M_PI);
    if (angle < 0)
        angle += ((360  * M_PI) / 180); 
    return angle;
}

 
void  draw_sprit(void *item)
{
     t_ray_sp *this = (t_ray_sp *) item;

   double dispro;
    double wallHei;
    double correctdis;
   
     double start;
     double end;
     double xsize;
     double ysize;



    double color;
  t_sp_texture *tsp;

        if(this->pos != NULL  && this->sp != NULL)
        {
          tsp = get_sp_tex(this->sp->kind);
           correctdis = this->length(this) * cos(this->angle -game->player.rotaion_angle);
           dispro = (game->width / 5) * tan(game->player.fov );
           wallHei = (game->wvalue / correctdis) * dispro;
           
                end = game->heigth /2  - wallHei / 2;
           start = this->index;
           
             
            
            end += game->player.offset;
           xsize = 1;
    t_line tang;
    double angle;
    double x_size; 
    tang.pos = this->sp->pos;

 
     angle = normelize_angel(atan2(this->pos->y - tang.pos->y , 
         this->pos->x - tang.pos->x))  + M_PI_2;
    
    angle = normelize_angel(angle);
    tang.dir = new_vector_pointer(tang.pos->x + (this->sp->rad * cos(angle)), 
        tang.pos->y + (this->sp->rad * sin (angle )));
       
            double dist =  get_line_distance(this) ;
            dist += this->sp->rad;
            if (tsp != NULL)
            {
              ysize = wallHei;
              xsize = 1;
              double nof = (dist / (2 * this->sp->rad)) * tsp->wsize;
             tsp->offset = nof + tsp->borders[2];
              tsp->offset = fabs(tsp->offset);
              render_sprite_texture((double []){start, end}, ysize, tsp, correctdis);
            }
            else
            {
               color =  shadow(0xff7272,  dist);
            rec(start,end, xsize, ysize ,color);
            }
        }
    free_ray_sp(this);
}
     








void free_player(void *item)
{
   t_player *pla;

   pla = (t_player *) item;
   pla->wall_rays.free(&pla->wall_rays, &free_ray);
   pla->sprit_rays.free(&pla->sprit_rays , &free_ray_sp);
   free(pla->pos);
}