# include "cub3d.h"
t_bool check_res_line(t_array_list lines)
{
  int i;
  char *l[2];
  if (lines.arr == NULL || lines.index != 2)
    return (FALSE);
  l[0] = lines.get(&lines,0);
  l[1] = lines.get(&line,1);
  if (l[0] ==NULL || l[1] == NULL)
    return (FALSE);
  i = 0;
  while (l[0][i] != '\0')
    i++;
}
void parse_resultion(t_parser *this , t_token *token)
{
  t_array_list word;
  char *line;
  int h;
  int w;

  if (this != NULL  && token != NULL && token->values.arr != NULL)
  {
    line = token->values.pull(&(token->values));
    new_array_list(&word,2,sizeof(char *));
      split_that(&word, line, ' ');
      if (check_res_line(word))
      {
        h = ft_atoi((char*)word.get(&word, 1));
        w = ft_atoi((char *) word.get(&word, 0));
        this->g->heigth = (h > 1440 || h <= 0) ? 1440 : h;
        this->g->width = (w > 2560 || w <= 0) ? 2560 : w;
        this->g->window.mlx = mlx_init();
        this->g->window.win =  mlx_new_window(this->g->window.mlx, 
        (int) this->g->width, (int) this->g->heigth , "CUB3d");
        this->g->window.img = (t_image *) malloc (sizeof(t_image));
        init_image(this->g->window.img, this->g->window);
        word.free(&word , &free);
        
      }
      else 
       put_error(this->g , ft_strdup("invalid resulotion"));
  }
  else
    put_error(this->g , ft_strdup("no resulotion"));
}

// t_bool check_res(t_array_list words)
// {
//   int i;
//   int r;
//   char *line;

//   i = 0;
//   r = 0;
//   if (words.index  == 3)
//     if (!ft_memcmp(words.get(&words , 0), "R",
//      ft_strlen((char *)words.get(&words , 0))))  
//     {  while(++r <words.index)
//       {
//         i = 0;
//         if ((line =  words.get(&words, r)) != NULL)
//            while (line[i++] != '\0')
//                 if(!ft_isdigit((int) line[i]))
//                     return (FALSE);
//         else
//           return (FALSE);
//       }
//         return (TRUE);
//     }
//   return (FALSE);
// }
// {
//     int h;
//     int w;
//     t_array_list word;

//     h = 0;
//     w = 0;
//     new_array_list(&word , 3, sizeof(char *));
//     split_that(&word, line , ' ');
//     if ( !check_res(word))
//       game->errors.push(&game->errors ,ft_strdup("invalid resulotion"),
//       sizeof(char *));
//     else
//     {
        
//     }
// }

// t_bool find_res(t_game *g_p,t_array_list array)
// {
//   int i;
//   int r;

//   t_bool res_founded;
//   i = 0;
//   res_founded = find_res_loop(array);
  
//   if (res_founded == TRUE && g_p->errors.index != 0)
//       res_founded = FALSE;
//   else if (res_founded == FALSE)
//     g_p->errors.push(&g_p->errors ,ft_strdup("define resulotion please !"),
//         sizeof(char *));
//   return res_founded;
// }

// t_bool find_res_loop(t_array_list array)
// {
//   while (i < array.index)
//   {
//       int i;
//       int r;
//       t_bool res_founded;
//       char *line;

//       res_founded = FALSE;
//       i = 0;
//       r = 0;
//       line = (char *)array.get(&array, i);
//       if (line != NULL)
//       {
//         while (ft_iswhitespace(line[r]))
//           r++;
//         if(ft_strncmp(line + r , "R", 1) == 0)
//         {
//               res_founded = TRUE;
//               fill_res(g_p ,line );
//             break;
//         }
//       }
//       i++;
//     }

// }