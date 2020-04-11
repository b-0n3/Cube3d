#ifndef FT_PARSER_H
#define FT_PARSER_H

typedef struct s_parser{
        t_array_list lines;
        int             fd;
        struct s_game          *g_p;
        void (*get_lines)(struct s_parser *this);
        int (*get_fd)(char *filename);
        void  (*do_final)( struct s_parser *this);
        void (*free)(void *this);
}           t_parser;



void get_lines(t_parser *this);
int get_fd(char *filename);
void new_parser(t_parser *this, char *filename , t_game *g_p);
void  parser_do_final(t_parser *this);
void   free_parser(void *this);

#endif