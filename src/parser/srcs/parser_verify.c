#include "parser.h"

void verify_map(t_parser *this){
    t_token *token;
    int i;
    int j;
    char *line;
    size_t len;

    i = 0;
    token = get_token_by_key(this, "MAP");
    if(token == NULL || token->values.arr == NULL || token->values.index == 0)
       put_error(this->g,ft_strdup("no map!"));
    else
    {
        while (i++ <token->values.index)
        {
            j = 0;
            line = token->values.get(&(token->values),i);
            len = ft_stlen(line);
            while (j++ < len)
            {
                if (line[j] == ' ' || line[j] == '0')
            }
        }
    }
}