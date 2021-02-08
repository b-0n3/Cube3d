#include "cub3d.h"

t_wall *new_wall(t_vector *pos , t_vector *dir, int angle)
{
    t_wall *wall;

    wall = (t_wall *)malloc(sizeof(t_wall));
    wall->dir = dir;
    wall->pos = pos;
    wall->kind = angle;
    return wall;
}


