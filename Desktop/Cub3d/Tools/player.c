#include "Cube3d.h"

extern t_game *game;

void new_player(t_player *this , t_vector *pos, char ch)
{
    int nb_rays;
    double ray_angle;

    this->fov = 60 *( M_PI / 180);
    this->render= &render_player;
    this->pos = pos;
    this->mov_speed = 2.0;
    this->rotation_speed = this->mov_speed * (M_PI / 180);
    this->w_dir = 0;
    this->t_dir = 0;
    nb_rays = 5;
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
    while (nb-- >= 0)
    {
        ray_angle = normelize_angel(ray_angle);
        this->wall_rays.push(&this->wall_rays, new_ray(this->pos ,ray_angle) , sizeof(t_ray));
        ray_angle += (this->fov / nb_rays);
    }
}

double  normelize_angel(double angle)
{
    angle = fmod(angle , 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI); 
    return angle;
}

void update_player(t_player *this)
{
    double next_x;
    double next_y;

    if (this->w_dir != 0)
    {
        next_x = this->pos->x ;
    }
    if (this->t_dir != 0)
    {

    }
}

void draw_ray(void *item)
{
    t_ray *ray;

    ray = (t_ray *) item;
    if(ray != NULL)
    {
        ray->render(ray);
    }
}

void render_player(t_player *this)
{
    t_ray *direction;
    t_vector vu_pos;

    new_vector(&vu_pos , this->pos->x - 6, this->pos->y - 6);
    direction = new_ray(this->pos, this->rotaion_angle);
    draw_rec(game->window ,vu_pos ,12,  0xf6e1e1);
    draw_line(game->window,direction->pos, direction->dir, 0xff9d76);
    this->wall_rays.foreach(&this->wall_rays, &draw_ray);

}