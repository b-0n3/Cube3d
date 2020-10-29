#include "Cube3d.h"

/* 
  @autor : b0n3

    info :
      this file contains function that handle the sprite texture 
      and handle errors thought.
      - a sprite line 
       X |Y   Z   | ....
      x : how many texture in the line 
      Y : a number defines the kind  of  the texture 
      Z : the full path to the image
      
    toDo:
        create this function :
        sprite_tex_parser(line + i); 
          line_parser(t_array_list *sp_links, char *str)
          check_tex_kind()
          
 */

extern t_game *game;


/* 
  borders;
    0: where the real heigth starts;
    1: where the real heigth ends;
    2: where the real width starts;
    3: where the real width ends;
*/
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
    if (tex->hsize >0 && tex->wsize >0)
      return TRUE;
   return FALSE;
}

t_bool push_sp_texture(t_sp_texture *tex)
{
  return game->allocated_sp_tex.push(
  &game->allocated_sp_tex, 
  tex, sizeof(t_sp_texture));
}

t_bool line_parser( char *str)
{
  t_sp_texture *tex;
  t_array_list links;
  int kind;
  t_bool valid;

  valid = FALSE;
  new_array_list(&links,2,sizeof(char *));
  split_that(&links , str, ' ');
  if (links.index == 2)
  {
    kind = ((char *)links.get(&links, 0))[0] - 48;
    tex = new_sp_texture(links.get(&links, 1), kind);
    if (tex != NULL)
    {
      if (set_borders(tex))
        if (push_sp_texture(tex))
            valid = TRUE;
    }
  }
  links.free(&links, &free);
    return valid;
}

void  sprite_tex_parser(char *line)
{
  t_array_list data;
  char *l;
  int nb;

  new_array_list(&data ,3 , sizeof(char *));
  printf("\n %s\n", line);
  split_that(&data, line , '|'); 
  if (data.index > 0)
  {
    nb = ft_atoi(data.get(&data, 0));
    if (nb > 0 && nb == data.index - 1)
    {
      while (nb > 0)
      {
        if (!line_parser(data.get(&data, nb)))
        {
          game->errors.push(&game->errors,
          ft_strdup("invalid sp texture"),
          sizeof(char *));
          break;
        }
        nb--;
      }
    }
    else
      game->errors.push(&game->errors,
      ft_strdup("invalid sizeof sp texture"),
      sizeof(char *));
  }
  data.free(&data, &free);
}




