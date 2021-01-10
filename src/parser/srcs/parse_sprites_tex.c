#include "parser.h"

extern t_game *game;

t_bool push_sp_texture(t_sp_texture *tex)
{
  return game->allocated_sp_tex.push(
  &game->allocated_sp_tex, 
  tex, sizeof(t_sp_texture));
}

void parse_sprite(t_parser *this, t_token *token)
{
    int fd;
    char *filename;
    t_sp_texture *tex;


    if(this == NULL  || token == NULL)
        return;
    filename =(char *) token->values.pop(&(token->values));
    if(filename != NULL)
        fd = open(filename , O_RDONLY);
    if (filename == NULL || fd < 0)
        put_error(this , ft_strdup("invalid sprite texture"));
    else
    {
        tex = new_sp_texture(filename, 2);
        if(tex == NULL)
           put_error(this , ft_strdup("invalid sprite texture"));
        else
            if (set_borders(tex))
                if (!push_sp_texture(tex))
                    put_error(this , ft_strdup("invalid sprite texture"));
    }
}