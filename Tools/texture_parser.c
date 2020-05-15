#include "Cube3d.h"
int skip(char *line , int index, char ch)
{
  if (line == NULL || index < 0)
    return index < 0 ? 0 : index;
  while (line[index] == ch)
      index++;
  return index ;
}

void  split_that(t_array_list *words , char *line , char ch)
{
  int firstptr;
  int i;
  char *str;

  
  firstptr = skip(line, 0, ch) ;
  i = skip(line, 0, ch);
  while (line[i] != '\0')
  {
    while (line[i] != ch && line[i ] != '\0')
        i++;
    if (line[i] == ch || line[i] == '\0')
    {
        str = (char *) malloc((firstptr + i) + 1);
        ft_strlcpy(str , line + firstptr , i - firstptr + 1);
        words->push(words, str, sizeof (str));
        firstptr =  skip(line, i , ch) ;
        i = firstptr -1;
    }
    i++;
  }


}

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