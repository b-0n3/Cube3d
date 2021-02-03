#include "cub3d.h"

void parse_ea_tex(t_parser *this, t_token *token)
{
    char *filename;
    t_texture *tex;

    if (this != NULL)
    {
        if (token == NULL) 
            put_error(this->g , ft_strdup("no ea tex"));
        else{
         filename =(char *) token->values.pull(&(token->values));
    if(!ft_check_file(filename, ".xpm"))
        put_error(this->g , ft_strdup("invalid ea texture"));
    else
    {
        tex = new_texture(filename);
        if(tex == NULL)
           put_error(this->g , ft_strdup("invalid ea texture"));
        else
        {
            tex->data =  flip_w_arr(tex->data, tex->height * tex->width, tex->width);    
            this->g->ea_texture = tex;
        }
    }
        }
    }
}