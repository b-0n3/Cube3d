#include "Cube3d.h"
extern t_game *game;
int coli;

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





void update_sp_ray(t_ray_sp *this, t_vector *dir, t_sprites *sp)
{


    double diff_an;
    if (dir == NULL || sp == NULL)
         return ;
    if(this->dir != NULL)
        free(this->dir);
    this->dir = new_vector_pointer(dir->x, dir->y);
    this->sp = sp;
}

t_ray_sp *new_sp_ray(t_vector *pos, t_vector *dir,  double angle, int i, t_sprites *sp)
{
    t_ray_sp *ray;
    ray = (t_ray_sp *)malloc(sizeof (t_ray_sp));
    if (ray != NULL)
    {
        ray->pos = new_vector_pointer(pos->x, pos->y);
        ray->cast = &cast_ray;
        ray->length = &ray_sp_len;
        ray->free = &free_ray_sp;
        ray->update = &update_sp_ray;
        ray->dir = NULL;
        ray->angle = angle;
        ray->index = i;
        ray->update(ray, dir, sp);
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
        t_ray_sp   *sp = NULL;
        t_sprites *spp;
        while (index < game->sprites.index)
        {
            spp = game->sprites.get(&game->sprites, index);
            cast_sprite(new_vector_pointer(ray->pos->x, ray->pos->y), spp,
             &sp , ray->length(ray),ray->angle , ray->index);
            index++;
        }
        if(sp != NULL)
            game->player.sprit_rays.push(&(game->player.sprit_rays), sp , sizeof(t_ray));
        index = 0;
        sp = NULL;
        while (index < game->lights.index)
        {
          
             spp = game->lights.get(&game->lights, index);
            cast_sprite(new_vector_pointer(ray->pos->x, ray->pos->y), spp,
             &sp , ray->length(ray),ray->angle , ray->index);
            index++;
        }
        if(sp != NULL)
            game->player.light_rays.push(&(game->player.light_rays), sp , sizeof(t_ray_sp));
        
    }
 }

int pick_color(int kind, double correctdis)
{
  int color;

            if (kind == 0 )
            color = shadow(game->color[0] , correctdis);
            else  if (kind == 1)
            color = shadow(game->color[1] , correctdis) ;
            else  if (kind == 2)
            color = shadow(game->color[2] , correctdis) ;
            else    if (kind == 3)         
            color = shadow(game->color[3] , correctdis);
    return color;
}

t_texture *pick_texture(int kind)
{
  t_texture *tex;

  tex = NULL;

  if (kind == 0 )
  {
      if (game->n_texture != NULL)
        tex = game->n_texture;
  }
  else  if (kind == 2)
  {
      if (game->so_texture != NULL)
        tex = game->so_texture;
  } 
  else  if (kind == 1)
  {
      if (game->ea_texture != NULL)
        tex = game->ea_texture;
  }
  else if (kind == 3)            
  {
      if (game->we_texture != NULL)
        tex = game->we_texture;
  } 
  return tex;
}


void   render_wall_texture( double start , double end , double wallHei ,t_texture *tex , double dis)
{
      int color;
      t_vector pos;
      int y2 = end  + wallHei;
      float index;
       
      index = 0;
     
      float step = tex->height / wallHei;
      // if (step < 1)
      //   step = 1;
      //printf(" ---- %f -- \n", step);
      new_vector(&pos, start,end);
      while (pos.y < y2)
      {
          
          color = tex->data[(int)tex->offset   + (int) index * (int)tex->width];
          color = shadow (color , dis);
          image_put_pixel(game->window ,start , pos.y, color);
          pos.y += 1;
          index += step;
         // index = fmod(index, tex->height);
      }
      
     
}
void   render_sprite_texture( double start , double end , double wallHei ,t_sp_texture *tex , double dis);

// void render_floor(double drawEnd ,double distWall,double floorXWall,double floorYWall)
// {


//   double  distPlayer, currentDist;

     
//       distPlayer = 0.0;
//   if (drawEnd < 0) drawEnd = game->heigth; //becomes < 0 when the integer overflows

//       //draw the floor from drawEnd to the bottom of the screen
//       for(int y = drawEnd + 1; y < game->heigth; y++)
//       {
//         currentDist = game->heigth / (2.0 * y - game->heigth); //you could make a small lookup table for this instead

//         double weight = (currentDist - distPlayer) / (distWall - distPlayer);

//         double currentFloorX = weight * floorXWall + (1.0 - weight) * game->player.pos->x;
//         double currentFloorY = weight * floorYWall + (1.0 - weight) * game->player.pos->x;

//         int floorTexX, floorTexY;
//         floorTexX = (int)(currentFloorX * game->floor->width) %  game->floor->width;
//         floorTexY = (int)(currentFloorY *  game->floor->height) % game->floor->height;

//         //floor
//        // buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
//         //ceiling (symmetrical!)
//        // buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
//            int     color = game->floor->data[game->floor->width * floorTexX + floorTexY];
//          color = shadow(color , game->heigth  - y);
//       //  color = (color >> 1) & 8355711; // make a bit darker
        
//         image_put_pixel(game->window ,(int) floorXWall,y ,color);
//       }
// }

void    render_ray(t_ray *this)
{
    //this->cast(this);

    double dispro;
    double wallHei;
    double correctdis;
   //this->pos->to_string(this->pos);

    //this->dir->to_string(this->dir);
//     t_vector sub;

//    new_vector(&sub,this->pos->x - this->dir->x   ,this->pos->y - this->dir->y );
  // printf("\nnew one __________________________________________ \n");
   // if ((this->angle > M_PI_2 && this->angle < 3 *M_PI_2 ))
            //draw_line(game->window ,this->pos, this->dir, 0x2c786c);
   //else
       // draw_line(game->window ,this->dir,this->pos, 0x2c786c);

     double start;
     double end;
     double xsize;
     double ysize;
      int color;
      t_texture *tex;
        if(this->kind >= 0)
       {
         
           correctdis = this->length(this) * cos(this->angle - game->player.rotaion_angle);
           dispro = (game->width /2) * tan(game->player.fov /2);
           wallHei = (game->wvalue / correctdis) * dispro;
           //printf("dispro : %f     walhei : %f", dispro, wallHei);
           start = this->index ;
           
           end = ((game->heigth / 2) - (wallHei / 2));
           
           ysize = wallHei;
           xsize = 1;
           t_bool i_h = this->kind == 0 || this->kind == 2? TRUE : FALSE;

           t_bool isu = this->kind == 0 ? TRUE : FALSE;
           t_bool  isl = this->kind == 3 ? TRUE : FALSE;
           int y = this->dir->y /  game->hvalue -  1;
            if (this->kind == 2)
              y +=1;
            char *line = (char *)game->parser->lines.get(
              &game->parser->lines, 
            y);
           double offset;
            
                       offset = i_h == 1 ? fmod(this->dir->x ,game->wvalue)
                        :fmod(this->dir->y ,game->wvalue);

            if (game->floor == NULL) 
              rec(start, end + wallHei + game->player.offset, xsize,  
              game->heigth /2 - game->player.offset,
               game->color[4] );
              // else
              // render_floor(end + wallHei + game->player.offset ,correctdis,this->index,end + wallHei + game->player.offset);
               
             
          rec(start,0 , xsize,  game->heigth - end - wallHei + game->player.offset, game->color[5]);
           //if(start < game->width /4 || start > 3 * game->width /4)
            end += game->player.offset;
            int x = (this->dir->x /  game->hvalue) -1;
            if (this->kind == 1)
              x++;
             //printf("%s\n", line);
              t_sp_texture *text = NULL;
               if (line[x] == '2')
            {
              //printf("%s\n", line);
              text = get_sp_tex(this->kind + 1);
            }
            if(text != NULL)
            {
              double valu = text->width ;
              valu = game->hvalue/valu;
                text->offset = offset +  valu;
                
                
                text->offset = fmod(text->offset ,game->hvalue);
                text->offset = fabs(text->offset);
              //  text->offset += valu;
               render_sprite_texture(start ,  end , wallHei ,
                text , correctdis);
            }
          else
          {
            
          
           
              tex = pick_texture(this->kind);
               if (tex == NULL)
              {
                 color = pick_color(this->kind , correctdis); 
                 rec(start,end, xsize, ysize ,color);
              }
               else
               {
                    tex->offset = offset;
                        tex->offset = (tex->offset / game->wvalue) * tex->width;
                  render_wall_texture(start , end , wallHei , tex ,correctdis);
                }
          }
      }
            
 //       }
    // color = 0x2c786c;
    //     ft_line(this->pos->x, this->pos->y , floor(sub.length(&sub)),this->angle, color);
    // //ft_line(this->dir->x, this->dir->y, 1, this->angle);
    
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
