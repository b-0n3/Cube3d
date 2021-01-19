#include "cub3d.h"

t_bool bonus_sp_condition(void *item)
{
    t_token *token;

    token = (t_token *) item;
    if (token != NULL)
    {
        if (ft_strchr("123456789" ,token->token[0]))
            return (TRUE);
    }
    return (FALSE);
}

void  *map_token(void *item)
{
    t_token *token;
    char *ptr;
    char *tmp;
    size_t i;

    
    i = 0;
    ptr = NULL;
    token = (t_token *) item;
    if (token != NULL)
    {
        ptr = ft_strdup(token->token);
        if (ptr != NULL)
            while (i < token->values.index)
            {
                tmp = (char *) token->values.get(&(token->values), i);
                ptr = ft_strjoin(ptr, tmp);
            
            //    ptr = tmp;
                i++;
            }
    }
    return ptr;
}


void parse_sp_line(void *item)
{
    char *line;
    
    line = (char *)item;
    if(line != NULL)
    {
        printf("%s \n", line);
        sprite_tex_parser(line);
    }
}

void parse_sprite_bonus(t_parser *this){
   t_array_list *lines;

    if(this != NULL)
    {
        lines = this->tokens.filter(this->tokens,
         sizeof(char *), &bonus_sp_condition, &map_token);
         if (lines != NULL)
            lines->foreach(lines, &parse_sp_line);
    }
}