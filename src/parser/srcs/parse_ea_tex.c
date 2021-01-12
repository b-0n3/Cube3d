#include "parser.h"

void parse_ea_tex(t_parser *this, t_token *token)
{
    int fd;
    char *filename;
    t_texture *tex;

    if (this != NULL)
    {
        if (token == NULL) 
            put_error(this->g , ft_strdup("no ea tex"));
         filename =(char *) token->values.pop(&(token->values));
    if(filename != NULL)
        fd = open(filename , O_RDONLY);
    if (filename == NULL || fd < 0)
        put_error(this , ft_strdup("invalid ea texture"));
    else
    {
        tex = new_texture(filename);
        if(tex == NULL)
           put_error(this , ft_strdup("invalid ea texture"));
        else
        this->g->ea_texture = tex;
    }
    close(fd);
}