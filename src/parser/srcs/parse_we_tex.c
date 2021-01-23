#include "cub3d.h"
int  *flip_w_arr(int *real, size_t size, int width)
{
    int *ret;
    int i;
    int len;
    int j;

    
    i = 0;
    ret = (int *) malloc (size * sizeof(int));
    while (i <  size / width)
    {
        j = 0;
        len = width -1;
        while (j < width)
        {
            ret[j + i * width] = real[len + i * width];
         j++;
         len--;
        }
        i++;
    }
    free(real);
    return ret;
}

void parse_we_tex(t_parser *this, t_token *token)
{
    int fd;
    char *filename;
    t_texture *tex;

    if (this != NULL)
    {
        if (token == NULL) 
            put_error(this->g , ft_strdup("no we tex"));
        else
        {
         filename =(char *) token->values.pull(&(token->values));
    if(filename != NULL)
        fd = open(filename , O_RDONLY);
    if (filename == NULL || fd < 0)
        put_error(this->g , ft_strdup("invalid we texture"));
    else
    {
        tex = new_texture(filename);
        
        if(tex == NULL)
           put_error(this->g , ft_strdup("invalid we texture"));
        else
        this->g->we_texture = tex;
    
    }
    }
    }
    close(fd);
}