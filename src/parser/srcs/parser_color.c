# include "cub3d.h"


void set_colors(t_game *g_p , char *line)
{
//     t_array_list *word;

//     word = (t_array_list *) malloc(sizeof(t_array_list));
//     if(word == NULL)
//     {
//         put_error(g_p , ft_strdup("memory error"));
//         return;
//     }
//     word = ft_split_property(line); 
// #ifdef BONUS
//    parse_fl_ci_tex(word, g_p);
// #else
//     parse_colors(word, g_p);
// #endif
//     word->free(word, &free);
//     free(word);
}

// void parse_fl_ci_tex(t_array_list word, t_game *g_p)
// {
//     char kind;
    
//      if (word.index == 2)
//     {
//       if (kind == 'f')
//         g_p->floor = new_sp_texture(word.get(&word,1), 10);
//       else if (kind == 'c')
//         g_p->ceil = new_sp_texture(word.get(&word,1), 11);
//     }
//     else
//       put_error(g_p,ft_strdup("invalid floor / ceiling texture"));
// }



// void parse_colors(t_array_list word, t_game *g_p)
// {
//     t_array_list colors;

//     if ( word.length != 2)
//         put_error(g_p,ft_strdup("invalid colors"));
//     else
//     {
//         new_array_list(&colors , 3, sizeof(char *));
//        split_that(&colors ,word.get(&word,1),  ',');
//        if(colors.length != 3)
//         put_error(g_p , ft_strdup("invalid colors"));
//         else
//         {
//             split_that();
//         }
        
//     }
    
// }