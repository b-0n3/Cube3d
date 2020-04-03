#include "Cube3d.h"

extern t_game *game;
 int nb_rays;
void new_player(t_player *this , t_vector *pos, char ch)
{
   
    double ray_angle;

    this->fov =  M_PI_4;
    this->render= &render_player;
    this->pos = pos;
    this->mov_speed = 7.0;
    this->update = &update_player;
    this->rotation_speed = 10 * (M_PI / 180);
    this->w_dir = 0;
    this->t_dir = 0;
    nb_rays = 50;
    if (ch == 'N')
        this->rotaion_angle =  (M_PI_2);
    else if (ch == 'S')
        this->rotaion_angle =  (3 * M_PI_2);
    else if (ch == 'W')
        this->rotaion_angle = M_PI;
    else
        this->rotaion_angle = 0.0f;
    new_array_list(&(this->wall_rays) ,10 , sizeof (t_ray));
    ray_angle = this->rotaion_angle - (this->fov / 2);
    int nb = nb_rays;
    while (nb-- > 0)
    {
        
        ray_angle = normelize_angel(ray_angle);

        this->wall_rays.push(&this->wall_rays, new_ray(this->pos ,ray_angle) , sizeof(t_ray));
        ray_angle = ray_angle + (this->fov / nb_rays);
    }
}

double  normelize_angel(double angle)
{
    angle = fmod(angle , 2 * M_PI);
    if (angle < 0)
        angle += ((360  * M_PI) / 180); 
    return angle;
}

void update_player(t_player *this)
{
    double next_x;
    double next_y;

    double ray_angle;

    this->rotaion_angle += (this->rotation_speed *this->t_dir);
   
    next_x =  this->pos->x  + cos(this->rotaion_angle) *(this->mov_speed * this->w_dir);
     next_y =  this->pos->y  + sin(this->rotaion_angle) *(this->mov_speed * this->w_dir);
    char *line = (char *) game->parser->lines.get(&game->parser->lines, floor(next_y  / game->hvalue));
    if(line[(int )floor (next_x / game->wvalue)]  != '1')
    {
            this->pos->x = next_x;
            this->pos->y = next_y;
        int index = 0;
        ray_angle = this->rotaion_angle - (this->fov / 2);
        while (index < this->wall_rays.index)
        {
            ray_angle = normelize_angel(ray_angle);
            t_ray *ray = (t_ray *) this->wall_rays.get(&this->wall_rays , index);
            if(ray != NULL)
            {
                ray->update(ray , ray_angle);
            }
            ray_angle = ray_angle + (this->fov / nb_rays);
            index++;
        }
    }
}

void draw_ray(void *item)
{
    t_ray *ray;

    ray = (t_ray *) item;
    if(ray != NULL)
    {
       // printf("hi %d \n", xccv);
        ray->render(ray);
        printf("this is kind %d \n" , ray->kind);
    }
}

void drawwall(void *item)
{
    t_wall *wall;
    t_vector sub;
    wall = (t_wall *) item;
    new_vector(&sub,wall->dir->x - wall->pos->x   ,wall->dir->y - wall->pos->y );
    ft_line(wall->pos->x, wall->pos->y, floor(sub.length(&sub)),wall->angle);
    //draw_line(game->window,wall->pos, wall->dir , 0xf8b400);
   // wall->dir->to_string(wall->dir);
    //wall->pos->to_string(wall->pos);
}

void render_player(t_player *this)
{
    t_ray *direction;
    t_vector vu_pos;

    new_vector(&vu_pos , this->pos->x - 6, this->pos->y - 6);
    direction = new_ray(this->pos, this->rotaion_angle);
    draw_rec(game->window ,vu_pos ,12,  0xf6e1e1);
    game->window.img->put_pixel(game->window,direction->dir->x, direction->dir->y, 0xff9d76);
    this->wall_rays.foreach(&this->wall_rays, &draw_ray);
    game->walls.foreach(&(game->walls), &drawwall);
    // printf("walls nb %ld",game->walls.index);

}