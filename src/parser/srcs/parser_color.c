# include "parser.h"


void set_colors(t_game *g_p , char *line, char kind)
{
    t_array_list word;
    t_array_list colors;

    new_array_list(&word , 3, sizeof(char *));
    new_array_list(&colors, 3, sizeof(char *));
    split_that(&word ,line,  ' ');
#ifdef BONUS
   parse_fl_ci_tex(word, g_p);
#else
    parse_colors(word, g_p);
#endif
    word.free(&word, &free);
    colors.free(&colors,&free);
}

void parse_fl_ci_tex(t_array_list word, t_game *g_p)
{
     if (word.index == 2)
    {
      if (kind == 'f')
        g_p->floor = new_sp_texture(word.get(&word,1), 10);
      else if (kind == 'c')
        g_p->ceil = new_sp_texture(word.get(&word,1), 11);
    }
    else
      put_error(g_p,ft_strdup("invalid floor / ceiling texture"));
}

void put_error(t_game *g_p, char *message)
{
    g_p->errors.push(&g_p->errors , message,
     sizeof (char *));
}

void parse_colors(t_array_list word, t_game *g_p)
{
    t_array_list colors;

    if ( word.length != 2)
        put_error(g_p,ft_strdup("invalid colors"));
    else
    {
        new_array_list(&colors , 3, sizeof(char *));
       split_that(&colors ,word.get(&word,1),  ',');
       if(colors.length != 3)
        put_error(g_p , ft_strdup("invalid colors"));
        else
        {
            split_that();
        }
        
    }
    
}