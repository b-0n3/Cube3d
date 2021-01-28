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
  door_d = posy < newy ?TRUE :FALSE;
  door_u = posy > newy ?TRUE :FALSE;
  door_r = posx < newx ?TRUE :FALSE;
  door_l = posx > newx?TRUE :FALSE;
  if (door_u )
    s_player_up(pos, newx , newy);
  else if(door_d)
    s_player_down(pos, newx , newy);
  else if(door_r)
  s_player_right(pos, newx , newy);
  else if(door_l)
    s_player_left(pos, newx , newy);
}

t_bool check_collision(t_player *player , double newx ,double newy)
{

    
    t_ray *ray;
    double newAngle;
    double ffangle;
    static int to;
    char *line;
    newAngle = player->rotaion_angle; 
    newAngle += player->w_dir == -1 ? M_PI: 0;
   newAngle += player->t_dir * player->rotation_speed;
    ffangle = player->rotaion_angle + player->t_dir * player->rotation_speed;
            normelize_angel(newAngle);
        ray = player->collision.get( &player->collision ,0);
        ray->angle = newAngle;
        free(ray->dir);
        ray->dir = ray->pos->get_dir_angle(ray->pos , ray->angle);
        ray->cast(ray);
      if (to == 0)
        to = 1;
        line = ((char *)game->parser->lines.get(&game->parser->lines, (int)newy));
        if(ray->coli == 1 || ft_strchr("50",line [(int) newx])==NULL)
        {
           newx = player->pos->x + (cos(player->rotaion_angle)* player->mov_speed);
         //  newy = player->pos->y +(sin(player->rotaion_angle) *player->mov_speed);
            if (player->t_dir != 0)
                to = player->t_dir;
            if(line[(int) (newx / game->hvalue)] != 's')
            {
            player->rotaion_angle = ffangle;
         //  if(player->t_dir == 0)
         //  {
             // player->rotaion_angle += player->rotation_speed * to;
               // player->vpos->y += player->dir->y * player->mov_speed * player->w_dir;
            
            }
            ray->coli = 0;
           
            newx /= game->hvalue;
           // newy /= game->hvalue;
            line = (char *)game->parser->lines.get(
              &game->parser->lines, 
            (int)newy);
              if(line != NULL)
                if (newx > 0 && newx < ft_strlen(line))
                {
                  if ( line [(int) newx] == 's')
                  {
                    update_secretdor_pos(player->pos , (int )newx,(int) newy);
                  
                  }
                }
            return TRUE;
        }
        else
        {
            player->pos->x = newx * game->wvalue;
            player->pos->y = newy * game->hvalue;
            player->rotaion_angle = ffangle;
            player->vpos->x += player->planx * ((player->mov_speed ) * -player->w_dir);
           player->vpos->y += player->plany * ((player->mov_speed )* -player->w_dir);


          float lastplanx = player->planx;
        player->planx = player->planx * cos((-player->rotation_speed  * player->t_dir ))
         - player->plany * sin(( -player->rotation_speed  * player->t_dir ));

         player->plany = lastplanx * sin( -player->rotation_speed * player->t_dir) 
        + player->plany * cos( -player->rotation_speed * player->t_dir) ;
     
  
 
  double oldDirX = player->dir->x;
       player->dir->x = player->dir->x * cos(-player->rotation_speed * player->t_dir)
        - player->dir->y * sin(-player->rotation_speed * player->t_dir);
        player->dir->y = oldDirX *  sin(-player->rotation_speed* player->t_dir)
         + player->dir->y * cos(-player->rotation_speed  * player->t_dir);
       
       
       
        }   
    
    return FALSE;
}
void update_player(t_player *this)
{
    double next_x;
    double next_y;

    double ray_angle;
    double newAngle ;
    double lastangle = this->rotaion_angle;
    newAngle =   this->rotaion_angle + (this->rotation_speed * this->t_dir);
     double lastx = this->pos->x;
     double lasty = this->pos->y;
    
   this->sprit_rays.index = 0;
    next_x =  this->pos->x  + cos(newAngle) *(this->mov_speed * this->w_dir);
     next_y =  this->pos->y  + sin(newAngle) *(this->mov_speed * this->w_dir);

    char *line = (char *) game->parser->lines.get(&game->parser->lines, (int)floor( (next_y ) / game->hvalue));
    
        check_collision(this ,next_x / game->wvalue , next_y / game->hvalue);
        int index = 0;
        ray_angle = this->rotaion_angle - (this->fov / 2);
        
            
        
         
      
           

       
        t_ray *ray;
        while (index < this->wall_rays.index)
        {
            ray_angle = normelize_angel(ray_angle);
            ray = (t_ray *) this->wall_rays.get(&this->wall_rays , index);
            if(ray != NULL)
            {
                ray->update(ray , ray_angle, index);
                ray_angle = ray_angle + (this->fov / nb_rays);
            }

            
            index++;
        }
      //  }
      
        }
    //}


     



double get_offset( t_line tang, t_ray_sp *ray)
{
    double newx;
    double newy;
    double new_len;
    float t = 0;
    float u = 0;
      double x3= ray->pos->x;
    double x4 = ray->dir->x;

    double x1 = tang.pos->x;
    double x2 = tang.dir->x;
   
    double y3 = ray->pos->y;
    double y4 = ray->dir->y;
    
    double y1 = tang.pos->y;
    double y2 = tang.dir->y;

    //new_vector(&sub , ray->pos->x, ray->pos->y);
    double den = (x1 - x2)*(y3 - y4) - (y1 -y2) * (x3-x4);
    free(tang.dir);
   if (den != 0)
   {
    t = ((x1 -x3) *(y3- y4 ) - (y1 - y3) *( x3 - x4))/ den;
    u = -((x1 -x2) * (y1 -y3) - (y1 - y2)*(x1 - x3))/den;
    //   printf ("%f \n ", t);
    return t * ray->sp->rad ;
    }
    return 0;
}
double get_line_distance(t_ray_sp *ray)
{
    t_line tang;
    double angle;
    double x_size;
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
     



 void cast_draw_floor(t_player *this)
 {
   t_ray *f_ray;
   t_ray *l_ray;
      float r_dirx0;
      float r_diry0;
      float r_dirx1;
      float r_diry1;
  
  
   //double diff =  game->width / game->heigth;
  for(int y = 0; y < game->heigth; y++)
    {
      
       r_dirx0 = this->dir->x - this->planx;
       r_diry0 = this->dir->y - this->plany;
       r_dirx1 = this->dir->x + this->planx;
       r_diry1 = this->dir->y + this->plany;

       double  p = y - (game->heigth / 2) ;
        p -= this->offset;

      // Vertical position of the camera.
      float posZ = 0.5 * game->heigth ;
        posZ -= this->offset;
      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = posZ / p;
      
      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = (rowDistance * (r_dirx1 - r_dirx0 ))/ game->width;
      float floorStepY = (rowDistance * (r_diry1 - r_diry0) )/ game->heigth;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX =  this->vpos->x + rowDistance * r_dirx0;
      float floorY =  this->vpos->y + rowDistance * r_diry0;
       for(int x = 0; x < game->width; ++x)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        double cellX =  floorX - floor(floorX);
        double  cellY = floorY - floor(floorY);

        // get the texture coordinate from the fractional part
        
        int tx = ( int)(game->floor->width /2 * (cellX) ) & ( game->floor->width -1 );
        int ty = (int)(game->floor->height /2  * (cellY) ) & (game->floor->height -1);

        
        floorX += floorStepX;
        floorY += floorStepY;
        
        int  color;

  
         color = game->floor->data[game->floor->width * ty + tx];
         color = shadow(color , game->heigth  - y);
        if (y > game->heigth /2  +  this->offset)
        image_put_pixel(game->window , x,y ,color);
      
       
        }
     
      }
       
   }
 





void free_player(void *item)
{
   t_player *pla;
   
   pla = (t_player *) item;

   pla->wall_rays.free(&pla->wall_rays, &free_ray);
   
   pla->sprit_rays.free(&pla->sprit_rays , &free_ray_sp);
   
   free(pla->pos);
}