# include "parser.h"

t_bool check_res(t_array_list words)
{
  t_bool valid;
  int i;
  int r;
  char *line;

  i = 0;
  r = 0;
  valid = FALSE;
  if (words.index  == 3)
    if (!ft_memcmp(words.get(&words , 0), "R",
     ft_strlen((char *)words.get(&words , 0))))  
    {  while(++r <words.index)
      {
        i = 0;
        if ((line =  words.get(&words, r)) != NULL)
           while (line[i++] != '\0')
                if(!ft_isdigit((int) line[i]))
                    return (FALSE);
        else
          return (FALSE);
      }
        return (TRUE);
    }
  return (FALSE);
}

void fill_res(t_game *g_p , char *line)
{
    int h;
    int w;
    t_array_list word;

    h = 0;
    w = 0;
    new_array_list(&word , 3, sizeof(char *));
    split_that(&word, line , ' ');
    if ( !check_res(word))
      game->errors.push(&game->errors ,ft_strdup("invalid resulotion"),
      sizeof(char *));
    else
    {
        h = ft_atoi((char*)word.get(&word ,2));
        w = ft_atoi((char *) word.get(&word, 1));
        g_p->heigth = (h > 1440 || h < 0) ? 1440 : h;
        g_p->width = (w > 2560 || w < 0) ? 2560 : w;
        g_p->window.mlx = mlx_init();
        g_p->window.win =  mlx_new_window(g_p->window.mlx, 
        (int) g_p->width, (int) g_p->heigth , "CUB3d");
        g_p->window.img = (t_image *) malloc (sizeof(t_image));
        init_image(g_p->window.img, g_p->window);
        word.free(&word , &free);
    }
}

t_bool find_res(t_game *g_p,t_array_list array)
{
  int i;
  int r;

  t_bool res_founded;
  i = 0;
  res_founded = find_res_loop(array);
  
  if (res_founded == TRUE && g_p->errors.index != 0)
      res_founded = FALSE;
  else if (res_founded == FALSE)
    g_p->errors.push(&g_p->errors ,ft_strdup("define resulotion please : "),
        sizeof(char *));
  return res_founded;
}

t_bool find_res_loop(t_array_list array)
{
  while (i < array.index)
  {
      int i;
      int r;
      t_bool res_founded;
      char *line;

      res_founded = FALSE;
      i = 0;
      r = 0;
      line = (char *)array.get(&array, i);
      if (line != NULL)
      {
        while (ft_iswhitespace(line[r]))
          r++;
        if(ft_strncmp(line + r , "R", 1) == 0)
        {
              res_founded = TRUE;
              fill_res(g_p ,line );
            break;
        }
      }
      
      i++;
    }

}