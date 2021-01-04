#ifndef FT_PARSER_H
#define FT_PARSER_H


#include "util.h"
#include "libft.h"

# include "game.h" 
# include "array_list.h"


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
void insert_wall(double s_x,double s_y,double e_x,double e_y);
void insert_player(double x,double y);
void push_n_walls(t_parser *this,char *l ,t_vector r_p);
t_bool check_res(t_array_list words);
void fill_res(t_game *g_p , char *line);
t_bool find_res(t_game *g_p,t_array_list array);
t_bool check_digit(char *line);
t_token *get_token_by_key(t_parser *this, char *key);
/*
 *** token 
*/
void new_token(t_token *this, t_array_list list);
t_bool token_push_values(t_token *this,t_array_list list);
t_bool token_push_value(t_token *this,char *line);


#endif