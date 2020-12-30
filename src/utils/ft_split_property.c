#include "ft_parser.h"

/* 
    ! you must  free *line after using this function 
    ! you should 
*/
t_array_list *ft_split_property(char *line, char *ch)
{
    t_array_list *words;
    int          i;
    char         *tmp;
    if (line != NULL && ch != NULL)
    {
        new_array_list(words,2,sizeof(char *));
        tmp = ft_strnstr(line, ch, (sizeof(*line) / sizeof(char));
        if (tmp !=  NULL)
        {
            i =0;
            // while ()
            return NULL;
        }
        
    }
    return words;
}