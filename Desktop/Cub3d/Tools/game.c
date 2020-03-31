#include "Cube3d.h"

void new_game(t_game *this, char *file_name)
{
    this->parser = (t_parser *) malloc (sizeof(t_parser));
    this->heigth = 0.0f;
    this->wvalue = 0.0f;
    new_array_list(&(this->errors), 3, sizeof(char *));
    new_array_list(&(this->walls), 3, sizeof(char *));
    new_parser(this->parser, file_name , this);
    this->exit = &__exit_;
    this->to_string = &game_to_string;
    this->free = &free_game;
    this->parser->do_final(this->parser);
    this->window.mlx = mlx_init();
    this->window.win =  mlx_new_window(this->window.mlx, (int) this->width, (int) this->heigth , "game");
    
    //this->parser->free(this->parser);

    //free(this->parser);
}

void __exit_(struct s_game *this , char *err_msg)
{
    
    if (err_msg != NULL)
    {
        perror(err_msg);
        this->free((void *)this);
        free(err_msg);
        exit(1);
    }
    exit(0);
}

char *game_to_string(struct s_game *this)
{
    return NULL;
}
void free_game(void *t)
{
    t_game *this  = (t_game *) t;
   // this->player.free(); 
   // this->sprit_rays.free(&(this->sprit_rays),this->sprit_rays.pull().free)
}

t_wall *new_wall(t_vector *pos , t_vector *dir)
{
    t_wall *wall;

    wall = (t_wall *)malloc(sizeof(t_wall));
    wall->dir = dir;
    wall->pos = pos;
    return wall;
}


