#include "cub3d.h"

int  *flip_arr(int *real, size_t size)
{
    int *ret;
    int i;
    int len;

    len = size - 1;
    i = 0;
    ret = (int *) malloc (size * sizeof(int));
    while (i < size)
    {
        ret[i] = real[len];
        i++;
        len--;
    }
    free(real);
    return ret;
}
void parse_so_tex(t_parser *this, t_token *token)
{

    char *filename;
    t_texture *tex;

    if (this != NULL)
    {
        if (token == NULL) 
            put_error(this->g , ft_strdup("no so tex"));
        else{
         filename =(char *) token->values.pull(&(token->values));
    if(!ft_check_file(filename, ".xpm"))
        put_error(this->g , ft_strdup("invalid so texture"));
    else
    {
        tex = new_texture(filename);
      
        if(tex == NULL)
           put_error(this->g , ft_strdup("invalid so texture"));
        else{
        this->g->so_texture = tex;
        }
    }
        }
    }
    
}