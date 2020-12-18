#include "Cube3d.h"




void set_no_tex(t_game *g_p , char *line)
{
    t_array_list words;

    new_array_list(&words , 3, sizeof(char *));
    split_that(&words, line, ' ');
  if ( words.index != 2)
    g_p->errors.push(&g_p->errors, ft_strdup("invalid  no texture path"),
     sizeof(char *));
  else
  {
    if (g_p->n_texture != NULL)
      g_p->errors.push(&g_p->errors, ft_strdup("diplicated no texture "),
     sizeof(char *));
     else
     {
       g_p->n_texture = new_texture((char *)words.get(&words , 1));
       if (g_p->n_texture == NULL)
        g_p->errors.push(&g_p->errors, ft_strdup("invalid  no texture file"),
          sizeof(char *));
     }
  }
  words.free(&words, &free);
}

void set_so_tex(t_game *g_p , char *line)
{
  t_array_list words;

    new_array_list(&words , 3, sizeof(char *));
    split_that(&words, line, ' ');
  if ( words.index != 2)
    g_p->errors.push(&g_p->errors, ft_strdup("invalid  so texture path"),
     sizeof(char *));
  else
  {
    if (g_p->so_texture != NULL)
      g_p->errors.push(&g_p->errors, ft_strdup("diplicated so texture "),
     sizeof(char *));
     else
     {
       g_p->so_texture = new_texture((char *)words.get(&words, 1));
       if (g_p->so_texture == NULL)
        g_p->errors.push(&g_p->errors, ft_strdup("invalid  so texture file"),
          sizeof(char *));
    }
  }
  words.free(&words, &free);
}

void set_we_tex(t_game *g_p , char *line)
{
   t_array_list words;

    new_array_list(&words , 3, sizeof(char *));
    split_that(&words, line, ' ');
  if ( words.index != 2)
    g_p->errors.push(&g_p->errors, ft_strdup("invalid  we texture path"),
     sizeof(char *));
  else
  {
    if (g_p->we_texture != NULL)
      g_p->errors.push(&g_p->errors, ft_strdup("diplicated we texture "),
     sizeof(char *));
     else
     {
       g_p->we_texture = new_texture((char *)words.get(&words, 1));
       if (g_p->we_texture == NULL)
            g_p->errors.push(&g_p->errors, ft_strdup("invalid  we texture file"),
             sizeof(char *));
     }
  }
  words.free(&words, &free);
}

void set_ea_tex(t_game *g_p , char *line)
{
  t_array_list words;

    new_array_list(&words , 3, sizeof(char *));
    split_that(&words, line, ' ');
  if ( words.index != 2)
    g_p->errors.push(&g_p->errors, ft_strdup("invalid  ea texture path"),
     sizeof(char *));
  else 
  {
    if (g_p->ea_texture != NULL)
      g_p->errors.push(&g_p->errors, ft_strdup("diplicated ea texture "),
     sizeof(char *));
     else
     {
       g_p->ea_texture = new_texture((char *)words.get(&words, 1));
       if (g_p->ea_texture == NULL)
        g_p->errors.push(&g_p->errors, ft_strdup("invalid  ea texture file"),
          sizeof(char *));
   }
  }
  words.free(&words, &free);
}