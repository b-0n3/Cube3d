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

typedef struct s_sp_texture
{
	int		*data;
	int	    width;
	int		height;
  int  kind;
  float   offset;
  int borders[4];
  float hsize;
  float wsize;
  t_image img;
  
}  t_sp_texture;

typedef	struct		s_texture
{
  float offset;
	int		*data;
  t_image img;
	int	        width;
	int		height;

}			t_texture;

typedef struct s_door
{
      t_vector *pos;
      t_sp_texture *tex;
      double    offset;
      t_bool isopen;
}       t_door;

typedef struct s_game{
        t_window window;
        t_texture *so_texture;
        t_texture *ea_texture;
        t_texture *n_texture;
        t_texture *we_texture;
        t_sp_texture *floor;
        t_sp_texture *ceil;
        int  color[6];
        double     hvalue;
        double     wvalue;
        int     heigth;
        int     width;
        int     bi;
        t_player  player;
        t_array_list lights;
        t_array_list allocated_sp_tex;
        t_array_list allocated_tex;
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


void  split_that(t_array_list *words , char *line , char ch);


/** texture functions  */
t_texture *new_texture(char *link);
t_sp_texture *new_sp_texture(char *link, int kind);
void set_no_tex(t_game *g_p , char *line);
void set_so_tex(t_game *g_p , char *line);
void set_we_tex(t_game *g_p , char *line);
void set_ea_tex(t_game *g_p , char *line);
t_sp_texture *get_sp_tex(int kind);
#endif 