#include "Cube3d.h"

void new_game(t_game *this, char *file_name)
{
    this->parser = (t_parser *) malloc (sizeof(t_parser));
    this->heigth = 0.0f;
    this->wvalue = 0.0f;
    this->bi = 0;
    new_array_list(&(this->errors), 10, sizeof(char *));
    new_array_list(&(this->walls), 10, sizeof(t_wall));
    new_array_list(&(this->sprites), 10, sizeof(t_sprites));
    new_parser(this->parser, file_name , this);
    this->exit = &__exit_;
    this->to_string = &game_to_string;
    this->free = &free_game;
    this->parser->do_final(this->parser);
    this->window.mlx = mlx_init();
    this->window.win =  mlx_new_window(this->window.mlx, (int) this->width, (int) this->heigth , "game");
    this->window.img = (t_image *) malloc (sizeof(t_image));
    init_image(this->window.img, this->window);
    //this->parser->free(this->parser);

    //free(this->parser);
}

void __exit_(struct s_game *this , char *err_msg)
{
    int ret = 1;
    if (err_msg != NULL)
    {
        perror(err_msg);
        
        free(err_msg);
        ret = 0;
    }
    this->free(this);
    exit(ret);
}

char *game_to_string(struct s_game *this)
{
    return NULL;
}

void free_game(void *t)
{
    t_game *this  = (t_game *) t;
    
   this->parser->free(this->parser);
   this->player.free(&this->player);
    this->errors.free(&this->errors ,&free);
    this->sprites.free(&this->sprites , &free_sprite);
    this->walls.free(&this->walls, &free_wall);
    mlx_clear_window(this->window.mlx, this->window.win);
    mlx_destroy_image(this->window.mlx, this->window.img->img_ptr);
    //free(this->window.img->img_data);
   // free(this->window.img);
  
    mlx_destroy_window(this->window.mlx, this->window.win);
    ////free(this->window.mlx);
 //   free(this->window.win);
}

t_wall *new_wall(t_vector *pos , t_vector *dir, int angle)
{
    t_wall *wall;

    wall = (t_wall *)malloc(sizeof(t_wall));
    wall->dir = dir;
    wall->pos = pos;
    wall->kind = angle;
    return wall;
}


