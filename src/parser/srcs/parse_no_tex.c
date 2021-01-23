#include "cub3d.h"

void parse_no_tex(t_parser *this, t_token *token)
{
    int fd;
    char *filename;
    t_texture *tex;

    if (this != NULL)
    {
        fd = -2;
        if (token == NULL) 
            put_error(this->g , ft_strdup("no no tex"));
        else{
         filename =(char *) token->values.pull(&(token->values));
    if(filename != NULL)
        fd = open(filename , O_RDONLY);
    if (fd < 0)
        put_error(this->g , ft_strdup("invalid no1 texture"));
    else
    {
        tex = new_texture(filename);
        if(tex == NULL)
           put_error(this->g , ft_strdup("invalid no2 texture"));
        else
        {
        tex->data =  flip_w_arr(tex->data, tex->height * tex->width, tex->width);    
        this->g->n_texture = tex;
        }
    }
        }
    }
}