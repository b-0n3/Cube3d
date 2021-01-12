#include "parser.h"

extern t_game *game;

t_bool push_sp_texture(t_sp_texture *tex)
{
  return game->allocated_sp_tex.push(
  &game->allocated_sp_tex, 
  tex, sizeof(t_sp_texture));
}

static t_bool is_empty(int *line, int size)
{
  int i;

  i = 0;
  while (i < size)
  {
      if (line[i] != 0 )
          return FALSE;
    i++;
  }
  return TRUE;
}

t_bool  set_borders(t_sp_texture *tex)
{
  int i;
  int j;
 
  i = 0;
  j = 0;
  if (tex->height <= 0 || tex->width <= 0)
    return FALSE;
  while(i++ < 4)
    tex->borders[i] = 0;
  i = 0;
  while (j++ < tex->height)
      if(!is_empty(tex->data + (j * tex->width), tex->width))
      {
        tex->borders[0] = j;
        break;
      }
  while (i++ < tex->width)
      if (tex->data[i + j * tex->width] != 0)
      {
        tex->borders[2] = i;
      }
  while (j++ < tex->height)
  {
    i =0;
    while (tex->data[i + j * tex->width] == 0 && i < tex->width)
        i++;
    if (tex->borders[2] > i)
       tex->borders[2] = i;
       i = tex->width -1;
    while (tex->data[i + j * tex->width] == 0 && i >=0)
        i--;
    if (tex->borders[3] < i)
       tex->borders[3] = i;
  }
  j = tex->height - 1;
  while (j-- >= 0)
    if(!is_empty(tex->data + (j * tex->width), tex->width))
      {
        tex->borders[1] = j;
        break;
      }
    tex->hsize = tex->borders[1] - tex->borders[0];
    tex->wsize = tex->borders[3] - tex->borders[2];
    if (tex->hsize >  0 && tex->wsize > 0)
      return TRUE;
   return FALSE;
}

void parse_sprite(t_parser *this, t_token *token, int kind)
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
        tex = new_sp_texture(filename, kind);
        if(tex == NULL)
           put_error(this , ft_strdup("invalid sprite texture"));
        else
            if (set_borders(tex))
                if (!push_sp_texture(tex))
                    put_error(this , ft_strdup("invalid sprite texture"));
    }
}