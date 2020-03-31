#include "Cube3d.h"

extern t_game *game;
void new_player(t_player *this , t_vector *pos, char ch)
{
    this->g = game;
    this->fov = (float) M_PI_2;
    this->render= &render_player;
    this->pos = pos;
    if (ch == 'N')
        this->rotaion_angle = (float) M_PI / 2;
    if (ch == 'S')
        this->rotaion_angle = (float)  3 * M_PI / 4;
    if (ch == 'W')
        this->rotaion_angle = (float) M_PI;
    else
        this->rotaion_angle = 0.0f;
    new_array_list(&(this->wall_rays) ,10 , )
}

void update_player(t_player *this)
{

}

void render_player(t_player *this)
{

}