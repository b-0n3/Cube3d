#include "Cube3d.h"

extern t_game *game;
 int nb_rays;
 extern int coli;
 int spsin = 0;
 int splin = 0; 
void new_player(t_player *this , t_vector *pos, char ch)
{
   
    double ray_angle;

    this->fov = 70 * (M_PI / 180);
    this->render= &render_player;
    this->pos = pos;
    this->mov_speed =8;
    this->update = &update_player;
    this->rotation_speed = 5 * 0.0174533;
    this->w_dir = 0;
    this->t_dir = 0;
    this->free = &free_player;
    nb_rays = game->width - 2;
    if (ch == 'N')
        this->rotaion_angle =  (M_PI_2);
    else if (ch == 'S')
        this->rotaion_angle =  (3 * M_PI_2);
    else if (ch == 'W')
        this->rotaion_angle = M_PI;
    else
        this->rotaion_angle = 0.0f;
    new_array_list(&(this->collision), 1, sizeof(t_ray));
    new_array_list(&(this->wall_rays) ,nb_rays, sizeof (t_ray));
    new_array_list(&(this->sprit_rays) ,14, sizeof (t_ray));
    ray_angle = this->rotaion_angle - (this->fov / 2);
    this->collision.push(&(this->collision),new_ray(this->pos , this->rotaion_angle , -10 ) , sizeof(t_ray));

    int nb = 0;
    while (nb < nb_rays)
    {
        ray_angle = normelize_angel(ray_angle);
        this->wall_rays.push(&this->wall_rays, new_ray(this->pos ,ray_angle,nb) , sizeof(t_ray));
        ray_angle = ray_angle + (this->fov / nb_rays);
        nb++;
    }
}

double  normelize_angel(double angle)
{
    angle = fmod(angle , 2 * M_PI);
    if (angle < 0)
        angle += ((360  * M_PI) / 180); 
    return angle;
}

t_bool check_collision(t_player *player , double newx ,double newy)
{

    
    t_ray *ray;
    double newAngle;
    double ffangle;
    static int to;
    if (to < -1 || to >1 || to== 0)
        to = 1;
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
        if(ray->coli == 1 || ((char *)game->parser->lines.get(&game->parser->lines, (int)newy))[(int) newx] != '0')
        {
            if (player->t_dir != 0)
                to = player->t_dir;
            player->rotaion_angle = ffangle;
         //  if(player->t_dir == 0)
         //  {
                player->rotaion_angle += player->rotation_speed * to;
         //   }
            ray->coli = 0;
            return TRUE;
        }
        else
        {
            player->pos->x = newx * game->wvalue;
            player->pos->y = newy * game->hvalue;
            player->rotaion_angle = ffangle;
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


void draw_ray(void *item)
{
    t_ray *ray;

    ray = (t_ray *) item;
    if(ray != NULL)
    {
       // printf("hi %d \n", xccv);
        ray->render(ray);
        //printf("this is kind %d \n" , ray->kind);
    }
}

void draw_sprit(void *item)
{
 //t_vector sub;
     t_ray *this = (t_ray *) item;
//     new_vector(&sub,this->pos->x - this->dir->x   ,this->pos->y - this->dir->y );
//     double color;
//      color =  shadow(0xf8b400 , this->length(this));
//      ft_line(this->pos->x, this->pos->y , floor(sub.len),this->angle, color);
   double dispro;
    double wallHei;
    double correctdis;
   
     double start;
     double end;
     double xsize;
     double ysize;
    double color;
       
        if(this->pos != NULL )
        {
           correctdis = this->length(this) * cos (game->player.rotaion_angle - this->angle);
           dispro = (game->width /2) * tan(game->player.fov /2);
           wallHei = (game->wvalue / correctdis) * dispro;
           

           start = this->index ;
           end = ((game->heigth /2));
           ysize = wallHei  * 0.7 ;
           xsize = 1;
            color =  shadow(0xff7272, correctdis) ;
            rec(start,end, xsize, ysize ,color);
        }


    free_ray_sp(this);
}

// void draw_sprites(void *item)
// {
// //    double dispro;
// //     double wallHei;
// //     double correctdis;
// //    //this->pos->to_string(this->pos);

// //     //this->dir->to_string(this->dir);
// //     t_vector sub;
// //     t_ray *this = (t_ray *) item;
// //     //new_vector(&sub,this->pos->x - this->dir->x   ,this->pos->y - this->dir->y );
// //   // printf("\nnew one __________________________________________ \n");
// //    // if ((this->angle > M_PI_2 && this->angle < 3 *M_PI_2 ))
// //             //draw_line(game->window ,this->pos, this->dir, 0x2c786c);
// //    //else
// //        // draw_line(game->window ,this->dir,this->pos, 0x2c786c);
// //      double start;
// //      double end;
// //      double xsize;
// //      double ysize;
// //     double color;
// //         color = 0xff7272;
// //         if(this->pos != NULL )
// //         {
// //            correctdis = this->length(this) * cos(this->angle - game->player.rotaion_angle);
// //            dispro = (game->width /2) * tan(game->player.fov /2);
// //            wallHei = (game->wvalue / correctdis) * dispro;
// //            //printf("dispro : %f     walhei : %f", dispro, wallHei);
// //            start = this->index ;
// //            end = ((game->heigth / 2) - (wallHei));
// //            ysize = wallHei / 2;
// //            xsize = 1;
// //             rec(start,end, xsize, ysize ,color);
// //         }
 
// t_sprites *sp = (t_sprites *) item;
// circle(*sp->pos, sp->rad ,0xff7272 );

//    // ft_line(wall->pos->x, wall->pos->y, floor(sub.length(&sub)),wall->angle);
//     //draw_line(game->window,wall->pos, wall->dir , 0xf8b400);
//    // wall->dir->to_string(wall->dir);
//     //wall->pos->to_string(wall->pos);
// }

void render_player(t_player *this)
{
    // t_ray *direction;
    // t_vector vu_pos;

    // new_vector(&vu_pos , this->pos->x - 6, this->pos->y - 6);
  //  direction = new_ray(this->pos, this->rotaion_angle);
   // draw_rec(game->window ,vu_pos ,12,  0xf6e1e1);
    //game->window.img->put_pixel(game->window,direction->dir->x, direction->dir->y, 0xff9d76);
    this->wall_rays.foreach(&this->wall_rays, &draw_ray);
   
   //game->sprites.foreach(&game->sprites , &draw_sprites);
   //this->sprit_rays.foreach(&this->sprit_rays , &draw_sprit);
    //spsin = ((t_ray *)(this->sprit_rays.get(&this->sprit_rays ,0)))->index; 
    splin = this->sprit_rays.index;
    do{
        t_ray *spray = (t_ray *)this->sprit_rays.pull(&this->sprit_rays);
        if(spray != NULL)
        {
            draw_sprit((void *)spray);
             
            
        }
        } while  (this->sprit_rays.index > 0 );
        spsin = 0;
        splin = 0;    
   // game->walls.foreach(&(game->walls), &drawwall);
    // printf("walls nb %ld",game->walls.index);

}
void free_player(void *item)
{
   t_player *pla;
   pla = (t_player *) item;

   pla->wall_rays.free(&pla->wall_rays, &free_ray);
   
   pla->sprit_rays.free(&pla->sprit_rays , &free_ray_sp);
   
   free(pla->pos);
}