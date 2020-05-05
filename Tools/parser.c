#include  "Cube3d.h"

t_game *game;

/* 
  @autor b0ne@1337 
  
  this file is for parser function
  ToDo:
    create fallowing functions:
      new_parser:
        this function should allocate and return a new  parser pointer
      do_final:
        this function should be the parsing entry point.
      ......
    continue setting up the parsin colors functions
    and create sprite texture function on another file 
    split this fucking file into files with five function each 
    to help with the  42 fucking norm d zeb 

      
*/
void new_parser(t_parser *this, char *filename, t_game *g_p)
{
    new_array_list(&(this->lines), 7, sizeof(char *));
    this->get_lines = &get_lines;
    this->get_fd = &get_fd;
    this->do_final = &parser_do_final;
    this->free = &free_parser;
    this->g_p = g_p;
    this->fd = this->get_fd(filename);
}

void get_lines(t_parser *this)
{
    char *line;
    int result;

    if (this->fd > -1)
    {
        while ((result = get_next_line(this->fd, &line)) > 0)
        {
            if (this->lines.push(&(this->lines), ft_strdup(line), sizeof(line)) != TRUE) 
                this->lines.free(&(this->lines), &free);
            free(line);
        }
        if (this->lines.push(&(this->lines),(void *) ft_strdup(line), sizeof(line)) != TRUE) 
            this->lines.free(&(this->lines), &free);
        free(line);
    }
    close(this->fd);
}

int get_fd(char *filename)
{
    int fd = -1;
    if (filename != NULL)
         fd = open(filename , O_RDONLY);
    return fd;
}


void   free_parser(void *th)
{
    t_parser *this;
    this = (t_parser *) th;
    this->lines.free(&this->lines ,&free);
    free(this);
}
t_bool check_res(t_array_list words)
{
  t_bool valid;
  int i;
  int r;
  char *line;

  i = 0;
  r = 0;
  valid = FALSE;
  if (words.index  == 4)
  {
    if (!ft_memcmp(words.get(&words , 0), "R",
     ft_strlen((char *)words.get(&words , 0))))  
    {
      while(++r <words.index)
      {
        i = 0;
        if ((line =  words.get(&words, r)) != NULL)
        {
           while (line[i] != '\0')
           {
                if(!ft_isdigit((int) line[i]))
                    return FALSE;
              i++;
           }
        }
        else
          return FALSE;
      }
        return TRUE;
    }
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
    {
      game->errors.push(&game->errors ,ft_strdup("invalid resulotion"),
      sizeof(char *));
    }
    else
    {
      h = ft_atoi((char*)word.get(&word ,2));
      w = ft_atoi((char *) word.get(&word, 1));
    }
    g_p->heigth = h < 600 ? h > 0 ? h :600 : 600;
    g_p->width =   w < 900 ? w > 0 ? w :900 : 900;
    g_p->window.mlx = mlx_init();
    g_p->window.win =  mlx_new_window(g_p->window.mlx, (int) g_p->width, (int) g_p->heigth , "game");
    g_p->window.img = (t_image *) malloc (sizeof(t_image));
    init_image(g_p->window.img, g_p->window);
    word.free(&word , &free);
}


t_bool check_digit(char *line)
{
  int i;

  i = 0;
  while (line[i++] != '\0')
    if (!ft_isdigit(line[i]))
        return FALSE;
  
  return i > 0 ? TRUE : FALSE;
}

void set_colors(t_game *g_p , char *line, char kind)
{
    t_array_list word;
    t_array_list colors;

    new_array_list(&word , 3, sizeof(char *));
    new_array_list(&colors, 3, sizeof(char *));
    split_that(&word ,line,  ' ');
    if (word.index == 2)
    {
      split_that(&colors ,word.get(&word, 1), ',');
      // if (colors.index == 3)
      //   if (check_digit(colors.get(&colors, 0)) && 
      //   check_digit(colors.get(&colors, 1)) && check_digit(colors.get(&colors, 2)))
      //    
         }
    game->errors.push(&game->errors , ft_strdup("invalid colors"),
     sizeof (char *));
    word.free(&word, &free);
    colors.free(&colors,&free);
}

void parse_line(t_game *g_p, char *line)
{
   if (line!= NULL)
   {
        if(ft_strncmp(line,"R", 1) == 0)
            fill_res(g_p ,line);
        else if (ft_strncmp(line,"NO", 2) == 0)
            set_no_tex(g_p , line);
        else if (ft_strncmp(line, "SO", 2) == 0)
            set_so_tex(g_p , line);
        else if (ft_strncmp(line, "WE", 2) == 0)
            set_we_tex(g_p , line);
        else if (ft_strncmp(line, "EA", 2) == 0 )
            set_ea_tex(g_p , line);
        else if (ft_strncmp(line, "S", 1))
            set_colors(g_p , line, 'S');
        else if (ft_strncmp(line, "F", 1))
            set_colors(g_p , line, 'f');
         else if (ft_strncmp(line, "C", 1))
            set_colors(g_p , line, 'c');
    }
}

t_bool check_mapline(char *line)
{
    int i;

    i = 0;
    if (line[i] == '\0')
        return FALSE;
    while ( line [i]  != '\0')
    {
        if (line[i] != ' ' && line[i] != '1')
            return FALSE;
        i++;
    }
    return (TRUE);
}

void get_w(void *item)
{
    char *l;
    int i;
    double wsize;

    l = (char *) item;
    if(ft_strlen(l ) <= 0)
        return;
    wsize = (double ) game->width / (double) (ft_strlen(l) + 1);
     if (wsize > game->bi)
      game->bi =(int) wsize;

    game->wvalue = 30;
 }

void push_n_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_d = this->lines.get(&(this->lines),r_p.y + 1);
    t_vector start;

    game = this->g_p;
    new_vector(&start , r_p.x , r_p.y);
    if (l_d != NULL)
     while (l[(int)r_p.x] != '\0' )
     {
                while (l[(int) r_p.x] == '1' && l_d[(int)r_p.x]!='1' )
                {
                    if ( l[(int) r_p.x] == '\0' || l_d[(int)r_p.x] == '\0')
                        break;
                    r_p.x += 1;
                }
                if (start.x < r_p.x)
                {
                    game->walls.push(&(game->walls),new_wall(new_vector_pointer(start.x * game->wvalue, (start.y + 1)*game->hvalue),new_vector_pointer((r_p.x )* game->wvalue ,(r_p.y + 1)*game->hvalue),0), sizeof(t_wall));
                   // printf("this is xx %d",xx);
                }
                 if(l[(int)r_p.x] == 'N' || l[(int)r_p.x] == 'S' || l[(int)r_p.x] == 'E' || l[(int)r_p.x] == 'W')
                {
                    
                  new_player(&(game->player), new_vector_pointer(r_p.x *game->wvalue + (0.5 * game->wvalue ), r_p.y * game->hvalue + (0.5 *game->hvalue)) ,l[(int)r_p.x]);
                    l[(int) r_p.x] = '0';
                }
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;
                
    }
}

void push_s_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_u = this->lines.get(&(this->lines),r_p.y - 1);
    t_vector start;

    game = this->g_p;
    new_vector(&start , r_p.x , r_p.y);
    if (l_u != NULL)
      while (l[(int)r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
     {
                while (l[(int) r_p.x] == '1' && l_u[(int)r_p.x] !='1' && l[(int) r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
                    r_p.x += 1;
                if (start.x < r_p.x)
                {
                   int xx= game->walls.push(&(game->walls),new_wall(new_vector_pointer(start.x * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((r_p.x )* game->wvalue ,(r_p.y )*game->hvalue),2), sizeof(t_wall));
                 //   printf("this is xx %d",xx);
                }
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;
                
    }
}

void push_e_walls(t_vector p)
{
    char *l = game->parser->lines.get(&game->parser->lines, p.y);
    t_vector start;
    new_vector(&start , p.x, p.y);
    int len;
    while (l != NULL && p.y < game->parser->lines.index)
    {
         l = game->parser->lines.get(&game->parser->lines, p.y);
        while (l[(int)p.x] == '1' && l[(int)p.x + 1] != '1')
        {
            p.y += 1;
            l = game->parser->lines.get(&game->parser->lines, p.y);
            if (l != NULL)
            {
                len = ft_strlen(l);
                if (p.x >= len)
                    break;
            }
            else 
                break;
        }

            if (start.y < p.y)
                {
                   int xx= game->walls.push(&(game->walls),new_wall(new_vector_pointer((start.x +1 ) * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((p.x + 1)* game->wvalue ,(p.y )*game->hvalue),3), sizeof(t_wall));
                 //   printf("this is xx %d",xx);
                }
                 p.y += 1;
                 start.x = p.x;
                 start.y = p.y;
    }
}


void push_w_walls(t_vector p)
{
char *l = game->parser->lines.get(&game->parser->lines, p.y);
    t_vector start;
    new_vector(&start , p.x, p.y);
    int len;
    while (l != NULL && p.y < game->parser->lines.index)
    {
         l = game->parser->lines.get(&game->parser->lines, p.y );
        while (l[(int)p.x] == '1' && l[(int)p.x - 1] != '1')
        {
            p.y += 1;
            l = game->parser->lines.get(&game->parser->lines, p.y);
            if (l != NULL)
            {
                len = ft_strlen(l);
                if (p.x >= len)
                    break;
            }
            else 
                break;
        }

            if (start.y < p.y)
                {
                   int xx= game->walls.push(&(game->walls),new_wall(new_vector_pointer((start.x ) * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((p.x)* game->wvalue ,(p.y )*game->hvalue),1), sizeof(t_wall));
                 //   printf("this is xx %d",xx);
                }
                 p.y += 1;
                 start.x = p.x;
                 start.y = p.y;
    }
}

void    get_walls(t_parser *this)
{
    t_vector real_pos;
    char *l;
    new_vector(&real_pos, 0 , 0);
    while (real_pos.y < this->lines.index)
    {
        real_pos.x = 0;
        l = (char *) this->lines.get(&this->lines , (int) real_pos.y);
           push_n_walls(this, l, real_pos);
           push_s_walls(this, l ,real_pos);
            real_pos.y += 1.0;
    }
   real_pos.x  =0;
   real_pos.y = 0;
   while (real_pos.x < game->bi)
   {
       push_e_walls(real_pos);
       if(real_pos.x > 0)
           push_w_walls(real_pos);
       real_pos.x += 1;
   }
}
void get_sprites(t_parser *this)
{
    int x;
    int y =0;
    char *l;
    while (y < this->lines.index)
    {
        x = 0;
        l = this->lines.get(&this->lines , y);
        while (l[x] != '\0')
        {
            if (l[x] != '1' && l[x] != '0'  && l[x] != ' ')
            {
                game->sprites.push(&game->sprites, new_sprite(new_vector_pointer((x + 0.5) * game->wvalue, (y + 0.5) * game->hvalue), game->hvalue * 0.3, l[x]),sizeof(t_sprites) );
            }
            x++;
        }
        y++;
    }
}

t_bool create_map(t_parser *this)
{
    int nb_lines = 0;

    while ( this->lines.get(&(this->lines), nb_lines))
    {
        if (((char *)this->lines.get(&(this->lines), nb_lines))[0] == '\0')
                break;
            nb_lines++;
    }
    game = this->g_p;
    //game->hvalue = game->heigth /(nb_lines + 1);
    game->hvalue = 30;
    this->lines.foreach(&(this->lines),&get_w);
    game->wvalue = 30;
    get_walls(this);
    get_sprites(this);
    return TRUE;
    //get_doors(this);
}

int nb_texture()
{
  int i;

  i = 0;
  if (game->n_texture != NULL)
    i++;
  if (game->ea_texture != NULL)
    i++;
  if (game->we_texture != NULL)
    i++;
  if (game->so_texture != NULL)
    i++;
  return i;
}

void on_one_texture()
{
  t_texture *tex;

  tex = NULL;
  if(game->ea_texture != NULL)
    tex = game->ea_texture;
  else if(game->n_texture != NULL)
    tex  =game->n_texture;
  else if (game->we_texture != NULL)
    tex = game->we_texture;
  else if (game->so_texture != NULL)
    tex = game->we_texture;
  if(tex != NULL)
  {
    game->ea_texture = tex;
    game->n_texture = tex;
    game->we_texture = tex;
    game->so_texture = tex;
  }
}

/* 
    ea  -> we;
    so -> no;
 */

void on_two_texture(){
  if (game->n_texture != NULL && game->so_texture == NULL)
    game->so_texture = game->n_texture;
  else if (game->n_texture == NULL && game->so_texture != NULL)
    game->n_texture = game->so_texture;
  if (game->we_texture != NULL && game->ea_texture == NULL)
    game->ea_texture = game->we_texture;
  else if (game->ea_texture != NULL && game->we_texture == NULL)
    game->we_texture = game->ea_texture;
  if (game->n_texture == NULL && game->so_texture == NULL)
  {
    game->so_texture = game->we_texture;
    game->n_texture = game->ea_texture;
  }
  else if (game->we_texture == NULL && game->ea_texture == NULL)
  {
    game->ea_texture = game->n_texture;
    game->we_texture = game->so_texture;
  }
}
void on_tree_texture()
{
  if(game->ea_texture == NULL)
    game->ea_texture = game->we_texture;
  else if(game->n_texture == NULL)
    game->n_texture = game->so_texture;
  else if (game->we_texture == NULL)
   game->we_texture = game->ea_texture;
  else if (game->so_texture == NULL)
   game->we_texture = game->n_texture;
} 

void check_tex()
{
  int nb_tex;
  nb_tex = nb_texture();
  if( nb_tex == 1)
    on_one_texture();
  else if( nb_tex == 2)
    on_two_texture();
  else if( nb_tex == 3)
    on_tree_texture();
}

void init_tex()
{
  game->ea_texture = NULL;
  game->n_texture = NULL;
  game->so_texture = NULL;
  game->we_texture = NULL;
  game->color[0] = 0xf8b400;
  game->color[1] = 0x2c786c;
  game->color[2] = 0xbb3b0e;
  game->color[3] = 0xdd7631;
  game->color[4] = 0xfaf5e4;
  game->color[5] = 0x004445;  
}
void   parser_do_final(t_parser *this)
{
    char *line;

    game = this->g_p;
    this->get_lines(this);
      init_tex();
    if (this->lines.index > 0)
    {
        while (!check_mapline(this->lines.get(&(this->lines),0)))
        {
            line = this->lines.pull(&(this->lines));
            if ( line == NULL)
            {
                this->g_p->errors.push(&(this->g_p->errors),ft_strdup("invalid file : "), sizeof(char *));
                return;
            }
            if (line[0] != '\0')
                parse_line(this->g_p, line);
            free(line);
        }
        if (create_map(this))
        {
          check_tex();
            return;
        }
    }
     this->g_p->errors.push(&(this->g_p->errors),ft_strdup("invalid file : "), sizeof(char *));
}