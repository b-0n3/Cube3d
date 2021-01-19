#ifndef FT_PARSER_H
#define FT_PARSER_H


#include "utils.h"
#include "libft.h"
#include "vector.h"
#include "get_next_line.h"

# include <fcntl.h>
# include <mlx.h>
# include "array_list.h"
# include "game.h" 

typedef struct s_token{
        char *token;
        t_array_list values;
        void (*free)(struct s_token *this);
}               t_token;

typedef struct s_parser{
        t_array_list lines;
        t_array_list tokens;
        int             fd;
        struct s_game          *g;
        void (*get_lines)(struct s_parser *this);
        int (*get_fd)(char *filename);
        void (*parse_file)(struct s_parser *this);
        void  (*do_final)( struct s_parser *this);
        void (*free)(void *this);
}           t_parser;

t_bool check_empty_line(char *line);
void get_lines(t_parser *this);
int get_fd(char *filename);
void new_parser(t_parser *this, char *filename , t_game *g_p);
void  parser_do_final(t_parser *this);
void   free_parser(void *this);
void sprite_tex_parser(char *line);
void push_w_walls(t_vector p);
void insert_e_wall(t_vector start, t_vector p);
void insert_wall(double s_x,double s_y,double e_x,double e_y);
void insert_player(double x,double y,char ch);
void push_n_walls(t_parser *this,char *l ,t_vector r_p);
void insert_s_wall(double s_x, double s_y, double e_x, double e_y);
void push_e_walls(t_vector p);
t_bool check_res(t_array_list words);
// void fill_res(t_game *g_p , char *line);
// t_bool find_res(t_game *g_p,t_array_list array);
// t_bool check_digit(char *line);
t_token *get_token_by_key(t_parser *this, char *key);
void parse_resultion(t_parser *this , t_token *token);
void parser_parse_file(t_parser *this);
void init_properties(t_array_list *words);
void push_bonus_sprites_properties(t_array_list *words);
void put_token(t_parser *p , t_array_list word);
void parse_token(void *item);
// void  create_map(char *line);
void verify_map(t_parser *this);
t_bool is_map_line(char *line);
t_bool is_map_character(char ch);
t_bool map_created();
t_bool is_empty_or_comment(char *line);
t_bool check_properties(char *token);
t_bool push_sp_texture(t_sp_texture *tex);
void parse_ceil(t_parser *this, t_token *token);
int parse_color(t_game *g, t_array_list rgb_colors);
int list_rgb_to_int(int *val);
void parse_ceilling_color(t_game *this, t_token *token);
void parse_floor(t_parser *this, t_token *token);
void push_s_walls(t_parser *this,char *l ,t_vector r_p);
void insert_n_wall(double s_x,double s_y,double e_x,double e_y);
void parse_floor_color(t_game *this, t_token *token);
void parse_floor_tex(t_game *this, t_token *token);
void parse_we_tex(t_parser *this, t_token *token);
void parse_so_tex(t_parser *this, t_token *token);
void parse_ea_tex(t_parser *this, t_token *token);
void parse_no_tex(t_parser *this, t_token *token);
void parse_sprite(t_parser *this, t_token *token, int kind);
int list_rgb_to_int(int *val);
void  create_map_p(t_parser *this);
t_bool create_map(char *line);
void parse_sprite_bonus(t_parser *this);
t_bool ft_is_empty(char *line);
/*
 *** token 
*/
void new_token(t_token *this, t_array_list list);
void new_empty_token(t_token *this, char *token);
t_bool token_push_values(t_token *this,t_array_list list);
t_bool token_push_value(t_token *this,char *line);

void parse_map(t_parser *this);

#endif