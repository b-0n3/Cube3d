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
/* 
   1100
   PS00
   1100
 */
void s_player_right(t_vector *pos,int newx , int newy)
{
char *line;
  int i;

  i = newx;
  line = (char *)game->parser->lines.get(&game->parser->lines, newy);
  if (line != NULL)
  {
    while (line[i] == 's')
      i++;
      if (line[i] == '0')
      {
        pos->y = (newy + 0.5) * game->hvalue;
          pos->x = (i + 0.5) * game->hvalue;
      }
  }
}
/* 
   1110
   sP00
   1111
 */
void s_player_left(t_vector *pos, int  newx , int newy)
{
  char *line;
  int i;

  i = newx;
  line = (char *)game->parser->lines.get(&game->parser->lines, newy);
  if (line != NULL)
  {
    while (i > 0 && line[i] == 's')
      i--;
      if (line[i] == '0')
      {
        pos->y = (newy + 0.5) * game->hvalue;
          pos->x = (i + 0.5) * game->hvalue;
      }
  }
}

/*
  10001
  10P01
  11s11
*/

void s_player_down(t_vector *pos,int  newx , int newy)
{
  char *line;
  int i;
  t_bool comp;

  comp = FALSE;
  i = newy;
  while (!comp)
  {
    line = (char *)game->parser->lines.get(&game->parser->lines, i);
    
    if (line != NULL)
    {
      if (check_empty_line(line) || newx > ft_strlen(line))
        break;
        if (ft_strchr("s0", line[newx]) == NULL)
          break;
        if (line[newx] == '0')
        {
          pos->y = (i + 0.5) * game->hvalue;
          pos->x = (newx + 0.5) * game->hvalue;
          comp = TRUE;
        }
        i++;
    }
    else
      break;
  }
}
/* 
  11s11
  10P01
  10001
*/

void s_player_up(t_vector *pos,int  newx , int newy)
{
  char *line;
  int i;
  t_bool comp;

  comp = FALSE;
  i = newy;
  while (!comp)
  {
    line = (char *)game->parser->lines.get(&game->parser->lines, i);
    
    if (line != NULL)
    {
      if (check_empty_line(line) || newx > ft_strlen(line))
        break;
        if (ft_strchr("s0", line[newx]) == NULL)
          break;
        if (line[newx] == '0')
        {
          
          pos->y = (i + 0.5) * game->hvalue;
          pos->x = (newx + 0.5) * game->hvalue;
          comp = TRUE;
        }
        i--;
    }
    else
      break;
  }
}


void update_secretdor_pos(t_vector *pos , int newx, int newy)
{
  t_bool door_l;
  t_bool door_u;
  t_bool door_d;
  t_bool door_r;
  int posx;
  int posy;
  posx =  pos->x / game->hvalue;
  posy = pos->y / game->hvalue;
  door_d = posy < newy ? TRUE :FALSE;
  door_u = posy > newy ? TRUE :FALSE;
  door_r = posx < newx ? TRUE :FALSE;
  door_l = posx > newx ? TRUE :FALSE;
  if (door_u )
    s_player_up(pos, newx , newy);
  else if(door_d)
    s_player_down(pos, newx , newy);
  else if(door_r)
  s_player_right(pos, newx , newy);
  else if(door_l)
    s_player_left(pos, newx , newy);
}





 double calculate_t_sprite(t_ray_sp *ray , t_line line, double den)
{
    return (( line.pos->x - ray->pos->x) 
    * ( ray->pos->y - ray->dir->y ) 
    - ( line.pos->y - ray->pos->y ) 
    * ( ray->pos->x - ray->dir->x)) / den;
}

double calculate_u_sprite(t_ray_sp *ray , t_line line, double den)
{
    return -(( line.pos->x - line.dir->x ) 
    * ( line.pos->y - ray->pos->y ) 
    - ( line.pos->y - line.dir->y )
    *( line.pos->x - ray->pos->x ))
    / den;

}

double calculate_den_sprite(t_ray_sp *ray, t_line line)
{
    return  ( line.pos->x - line.dir->x )
    *( ray->pos->y - ray->dir->y) -
     ( line.pos->y - line.dir->y ) 
    * ( ray->pos->x - ray->dir->x );
}

double get_offset( t_line tang, t_ray_sp *ray)
{
    
    double den;
    float t = 0;
    float u = 0;
  

  den = calculate_den_sprite(ray , tang);
  free(tang.dir);
   if (den != 0)
   {
    t =  calculate_t_sprite(ray, tang,den);
    u = calculate_u_sprite(ray ,tang,den);
    return t * ray->sp->rad ;
    }
    return 0;
}

double get_line_distance(t_ray_sp *ray)
{
    t_line tang;
    double angle;
    tang.pos = ray->sp->pos;

    angle = normelize_angel(atan2(ray->pos->y - tang.pos->y , 
         ray->pos->x - tang.pos->x))  + M_PI_2;
    
    angle = normelize_angel(angle);
    tang.dir = new_vector_pointer(tang.pos->x + (ray->sp->rad * cos(angle)), 
        tang.pos->y + (ray->sp->rad * sin (angle )));
    return get_offset( tang, ray);
}

	void   render_sprite_texture( double start , double end , double wallHei ,t_sp_texture *tex , double dis)
{
      int color;
      t_vector pos;
      int y2 = end  + wallHei ;
      float index;
       
      index = 0;
      float step = tex->height / wallHei;
      new_vector(&pos, start,end);
      //float ss = tex->width / tex->wsize;
      
      //index += tex->borders[0];
      while (pos.y < y2)
      {
  
          color = tex->data[(int)(tex->offset )   + (int) index * (int)tex->width];
          if(color > 0)
          {
            
            if (!(tex->kind == '5' - 48 && color == tex->data[0]))
            {
                if (tex->kind != '5' - 48 && tex->kind != 10)
                     color = shadow(color , dis);
              image_put_pixel(game->window ,start , pos.y, color);
            }
            //rec(start + ss, pos.y + ss, (int) ss, (int)ss ,color);
          }

          pos.y += 1;
          index += step;
         // index = fmod(index, tex->height);
      }
      
     
}
 
void  draw_sprit(void *item)
{
// t_vector sub;
     t_ray_sp *this = (t_ray_sp *) item;
   //  new_vector(&sub,this->pos->x - this->dir->x   ,this->pos->y - this->dir->y );
   
   //   color =  shadow(0xf8b400 , this->length(this));
   //  ft_line(this->pos->x, this->pos->y , floor(sub.len),this->angle, color);
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
           correctdis = this->length(this) * cos(this->angle -game->player.rotaion_angle  );
           dispro = (game->width / 5) * tan(game->player.fov );
           wallHei = (game->wvalue / correctdis) * dispro;
           
       // printf ( "thsi is the offset  %d  \n ", this->offset);
       //tsp->kind == ('5' - 48) || tsp->kind == ('9' - 48)
            // if (tsp->height <= wallHei)
            //       end = ((game->heigth /2));
            // else
                end = game->heigth /2  - wallHei / 2;
           start = this->index;
           
             
            // if(tsp->borders[0] > 10)
            
            end += game->player.offset;
           xsize = 1;
              //  printf ("%f \n " , get_line_distance(this));
    t_line tang;
    double angle;
    double x_size;
     // this->sp->rad = tsp->width / 2;
    tang.pos = this->sp->pos;

 
     angle = normelize_angel(atan2(this->pos->y - tang.pos->y , 
         this->pos->x - tang.pos->x))  + M_PI_2;
    
    angle = normelize_angel(angle);
    tang.dir = new_vector_pointer(tang.pos->x + (this->sp->rad * cos(angle)), 
        tang.pos->y + (this->sp->rad * sin (angle )));
        //  new_vector(&sub,tang.pos->x - tang.dir->x   ,tang.pos->y - tang.dir->y );
             
   // ft_line(tang.pos->x, tang.pos->y , floor(sub.len), angle, color);
                //printf ("%f \n" , dist);
           
             
            double dist =  get_line_distance(this) ;
            dist += this->sp->rad;
             //end = game->heigth /2 - tsp->height / 2;
            
            //  ysize = (game->hvalue / correctdis) * dispro;
          
            if (tsp != NULL)
            {
              ysize = wallHei;
           // ysize = fmod(ysize, game->heigth);

              xsize = 1;
           
              double nof = (dist / (2 * this->sp->rad)) * tsp->wsize;
            
             tsp->offset = nof + tsp->borders[2];
              // if (tsp->kind == '5' -48)
              //   tsp->offset += (tsp->wsize / 4);
              tsp->offset = fabs(tsp->offset);
           // while ()
              render_sprite_texture(start, end, ysize, tsp, correctdis);
            }
            else
            {
            //printf("start %f  end  %f  size %f \n", start , end ,ysize );
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