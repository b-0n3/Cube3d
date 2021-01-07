#include "parser.h"

void verify_map(t_parser *this){
    t_token *token;
    t_vector pos;

    token = get_token_by_key(this, "MAP");
    if(token == NULL || token->values.arr == NULL || token->values.index == 0)
       put_error(this->g,ft_strdup("no map!"));
    else
    {
        new_vector(&pos, 0, 0);
        verify_map_lines(this, token->values,pos);
    }
}

void verify_map_lines(t_parser *this,t_array_list list,t_vector pos)
{
    char *line;
    size_t len;

    if (pos.x >= list.index || pos.x <0)
        return;    
    line  = list.get(&(list),pos.x);
    if (line == NULL)
        return;


}