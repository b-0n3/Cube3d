#ifndef FT_GAME_H
#define FT_GAME_H

# include "array_list.h"
# include "player.h"

# include "ray.h"

typedef struct s_wall{
        t_vector  *pos;
        t_vector  *dir;
        int     kind;
}               t_wall;



typedef struct s_sptites{
        t_vector *pos;
        double    rad;
        int kind;
        double u_a;
        double d_a;
        double a_p_r;
        void (*free)(void *item);
}       t_sprites;
 
typedef struct s_window {
            void *mlx;
            void *win;
            struct s_image *img;
}                t_window;

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
        void (*save)(struct s_game *this);
        void (*exit)(struct s_game *this , char *err_msg);
        void (*free)(void *this);
}               t_game;
# include "parser.h"
void save_game(t_game *this);
void    get_intesection_wall(t_ray *ray, t_wall wall);
double calculate_t(t_ray *ray , t_wall wall, double den);
double calculate_u(t_ray *ray , t_wall wall , double den);
double calculate_den(t_ray *ray, t_wall wall);
void new_game(t_game *this, char *file_name);
void __exit_(struct s_game *this , char *err_msg);

void free_game(void *this);





/** texture functions  */
t_texture *new_texture(char *link);
t_sp_texture *new_sp_texture(char *link, int kind);
void set_no_tex(t_game *g_p , char *line);
void set_so_tex(t_game *g_p , char *line);
void set_we_tex(t_game *g_p , char *line);
void set_ea_tex(t_game *g_p , char *line);
t_sp_texture *get_sp_tex(int kind);
t_texture *pick_texture(int kind);
void   render_sprite_texture( double p[] , double wallHei ,t_sp_texture *tex , double dis);

t_wall *new_wall(t_vector *pos , t_vector *dir, int angle);
void free_wall(void  * item);

void    init_image(t_image *this,t_window win);
void clear_screen( t_window s_win);
void show_image(t_window s_win);

/*     sprites functions*/
t_sprites *new_sprite(t_vector *pos, double rad , int kind);
void free_sprite(void *item);
void cast_sprite(t_vector *pos, t_sprites *sp, t_ray_sp **ray_sp ,t_ray *ray);
void   render_wall_texture( double p[] , double wallHei ,t_texture *tex , double dis);
#endif 