#ifndef FT_GAME_H
#define FT_GAME_H

typedef struct s_window {
            void *mlx;
            void *win;
            struct s_image *img;
}               t_window;

typedef struct s_image
{
        int     bpp;
        int     size_line;
        int     endian;
        void    *img_ptr;
        char    *img_data;
        int      len;
        void (*clear)(t_window s_win);
        void (*show)(t_window s_win);
        void (*put_pixel)(t_window v, int x, int y , int color);
}       t_image;

typedef struct s_game{
        t_window window;
        
        double     hvalue;
        double     wvalue;
        int     heigth;
        int     width;
        int     bi;
        t_player  player;

        t_array_list errors;
        t_array_list walls;
        t_array_list sprites;
        t_array_list doors;
        struct s_parser    *parser;
        void (*exit)(struct s_game *this , char *err_msg);
        char *(*to_string)(struct s_game *this);
        void (*free)(void *this);
}               t_game;

void new_game(t_game *this, char *file_name);
void __exit_(struct s_game *this , char *err_msg);
char *game_to_string(struct s_game *this);
void free_game(void *this);

#endif 