# ifndef FT_CUB_H
# define FT_CUB_H
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>
# include "get_next_line.h"



typedef int  t_bool;
#define TRUE 1
#define FALSE 0


typedef struct s_vector{
    double x;
    double y;
    double len;

    double (*length)(struct s_vector *this);
    void (*add)(struct s_vector *this , struct s_vector *o);
    void (*sub)(struct s_vector *this, struct s_vector *o);
    int (*compare_to)(void  *this , void *o);
    struct s_vector *(*get_dir_angle)(struct s_vector *this , double angle);
    void (*to_string)(void *item);
}              t_vector;


typedef struct s_array_list{
        void **arr;
        size_t index;
        size_t length;
        size_t size_of_object;
        t_bool (*push)(struct s_array_list *this, void *value ,size_t size_of_item);
        void *(*get)(struct s_array_list *this, size_t index);
        t_bool (*check_size)(struct s_array_list *this);
        t_bool (*check_data_type)(struct s_array_list *this, void *value, size_t size_of_item);
        t_bool (*new_array_double_size)(struct s_array_list *this);
        void (*foreach)(struct s_array_list *this ,void (*f)(void *item));
        void (*delete_if)(struct s_array_list *this, t_bool(*cond)(void *item),void (*fe)(void *item));
        void (*sort)(struct s_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r);
        void (*free)(struct s_array_list *this , void (*fe)(void *item));
        t_bool (*update_at)(struct s_array_list *this, void *value, size_t index);
        void (*swap)(void **a, void **b);
        void *(*pull)(struct s_array_list *this);

}               t_array_list;



typedef struct s_player{
    t_vector    *pos;
    double       rotaion_angle;
    double       fov;
    double      rotation_speed;
    double      mov_speed;
    int         w_dir;
    int         t_dir;
        t_array_list collision;
    t_array_list wall_rays;
    t_array_list sprit_rays;
    void (*update)(struct s_player *this);
    void (*render)(struct s_player *this);
    void (*free)(void *item);
}       t_player;



typedef struct s_ray{
        t_vector *pos;
        t_vector *dir;
        double   len;
        int     kind;
        double   angle;
        int index;
        int coli;
        void (*update)(struct s_ray *this, double angle, int i);
        void    (*cast)(void *ray);
        void    (*render)(struct s_ray *this);
        double (*length)(struct s_ray *this);
        void (*free)(void *item);
}       t_ray;

typedef struct s_ray_sp{
        t_vector *pos;
        t_vector *dir;
        double   len;
        int     kind;
        double   angle;
        int index;
        double dist;
        void    (*cast)(void *ray);
        void    (*render)(struct s_ray *this);
}t_ray_sp;
typedef struct s_wall{
        t_vector  *pos;
        t_vector  *dir;
        int     kind;
}               t_wall;

// typedef struct s_input{
// 	t_player *player;
//         void (*update)(struct s_input *this);
// }	t_input;

typedef struct s_sptites{
        t_vector *pos;
        double    rad;
        int kind;
        void (*free)(void *item);
}       t_sprites;

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

typedef struct s_parser{
        t_array_list lines;
        int             fd;
        struct s_game          *g_p;
        void (*get_lines)(struct s_parser *this);
        int (*get_fd)(char *filename);
        void  (*do_final)( struct s_parser *this);
        void (*free)(void *this);
}           t_parser;


/*  Vector  functions */
t_vector new_vector(t_vector *this,  double x, double y);
t_vector *new_vector_pointer(double x, double y);
t_vector *dir_from_angle(t_vector *this, double angle);
double length(t_vector *this);
void add(t_vector *this , t_vector *o);
void sub(t_vector *this, t_vector *o);
int compare_to(void  *this , void *o);
void vector_to_string(void *item);

double  normelize_angel(double angle);
/*   arraylist functions */
t_array_list *new_array_list(t_array_list *this, size_t first_size, size_t __sizeofit);
t_bool push(t_array_list *this, void *value, size_t size_of_item);
void *get(t_array_list *this, size_t  index);
t_bool check_size(t_array_list *this);
t_bool check_data_type(t_array_list *this, void *value, size_t size_of_item);
t_bool new_array_double_size(t_array_list *this);
void foreach(t_array_list *this ,void (*f)(void *item));
void delete_if(t_array_list *this, t_bool(*cond)(void *item), void (*fe)(void *item));
void sort(t_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r);
void _free(t_array_list *this, void (*fe)(void *item));
void ft_swap(void **a, void **b);
t_bool update_at(struct s_array_list *this, void *value, size_t index);
void *pull(t_array_list *this);

/*    parser function  */

void get_lines(t_parser *this);
int get_fd(char *filename);
void new_parser(t_parser *this, char *filename , t_game *g_p);
void  parser_do_final(t_parser *this);
void   free_parser(void *this);

/*    game  */

void new_game(t_game *this, char *file_name);
void __exit_(struct s_game *this , char *err_msg);
char *game_to_string(struct s_game *this);
void free_game(void *this);

/* wall function */
t_wall *new_wall(t_vector *pos , t_vector *dir, int angle);
void free_wall(void  * item);

/* player functin */
void new_player(t_player *this , t_vector *pos, char ch);
void update_player(t_player *this);
void render_player(t_player *this);
void free_player(void *item);


/* ray  function*/
t_ray *new_ray(t_vector *pos, double angle, int i);
void    cast_ray(void *ray);
void    render_ray(t_ray *this);
void update_ray(t_ray *this, double angle, int i);
void free_ray(void *item);

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
t_ray *new_ray_with_dir(t_vector *pos,t_vector *dir,  double angle, int i);
void    cast_sprite(t_vector *pos, t_sprites *sp, t_ray **ray_sp , double r_len, double angle, int index);
void free_ray_sp(void *item);
# endif
