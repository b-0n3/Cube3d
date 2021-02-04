#include "cub3d.h"

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

void set_borders_c(t_sp_texture *tex, int i , int j)
{
   while (j++ < (tex->height - 1))
  {
    i =0;
    while (tex->data[i + j * tex->width] == 0 && i <= tex->width)
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
        tex->borders[2] = i;
    set_borders_c(tex, i , j);
    tex->hsize = tex->borders[1] - tex->borders[0];
    tex->wsize = tex->borders[3] - tex->borders[2];
    if (tex->hsize >  0 && tex->wsize > 0)
      return TRUE;
   return FALSE;
}

void parse_sprite(t_parser *this, t_token *token, int kind)
{
    char *filename;
    t_sp_texture *tex;

    if(this == NULL  || token == NULL)
        return;
    filename =(char *) token->values.pull(&(token->values));
    if(!ft_check_file(filename, ".xpm"))
        put_error(this->g , ft_strdup("invalid sprite texture"));
    else
    {
        tex = new_sp_texture(filename, kind);
        if(tex == NULL)
           put_error(this->g , ft_strdup("invalid sprite texture"));
        else
            if (set_borders(tex))
                if (!push_sp_texture(tex))
                    put_error(this->g , ft_strdup("invalid sprite texture"));
    }
}