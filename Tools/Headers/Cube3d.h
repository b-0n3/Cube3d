# ifndef FT_CUB_H
# define FT_CUB_H
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>

# include "get_next_line.h"
# include "array_list.h"
# include "ray.h"
#include "player.h"
#include "game.h"
# include "parser.h"


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



/* wall function */
t_wall *new_wall(t_vector *pos , t_vector *dir, int angle);
void free_wall(void  * item);



/*  graphics function */
void  draw_line(t_window wi ,t_vector *pos , t_vector *dir , int color);
void draw_rec(t_window wi ,t_vector pos , int size , int color);
void    ft_line(float x, float y, int size ,float angle, int color);
void    init_image(t_image *this,t_window win);
void clear_screen( t_window s_win);
void show_image(t_window s_win);
void image_put_pixel(t_window v , int x, int y, int color);
void rec(int  x ,int  y, int  sizex ,int sizey, int color);
int		shadow(int color, double distance);
void	circle(t_vector a, int radius, int color);
void	line(int x0, int y0, int x1, int y1, int color);


/*          input    */
int key_pressed(int k_code , void *ptr);
int key_relased(int k_code , void *ptr);



/*     sprites functions*/
t_sprites *new_sprite(t_vector *pos, double rad , int kind);
void free_sprite(void *item);
void    cast_sprite(t_vector *pos, t_sprites *sp, t_ray_sp **ray_sp , double r_len, double angle, int index);

# endif
