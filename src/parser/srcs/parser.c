#include  "parser.h"

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
    continue setting up the parsing colors functions
    and create sprite texture function on another file 
    split this fucking file into files with five function each 
    to help with the  42 fucking norm d zeb 

      
*/




t_bool check_digit(char *line)
{
  int i;

  i = 0;
  while (line[i++] != '\0')
    if (!ft_isdigit(line[i]))
        return FALSE;
  
  return i > 0 ? TRUE : FALSE;
}






t_bool check_empty_line(char *line)
{
  int i;

  i = 0;
  
    if (line [0] == '#')
      return TRUE;
    while (line [i] != '\0')
    {
      if (!ft_iswhitespace(line[i]))
          return FALSE;
      i++;
    }
  
  return TRUE;
}

t_bool check_mapline(char *line)
{
    int i;

    i = 0;
    if (line[i] == '\0' || check_empty_line(line))
        return FALSE;
    while ( line [i]  != '\0')
    {
        if ( ft_isalpha(line[i]))
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
    // if (wsize > game->bi)
      if(ft_strlen(l) > game->bi)
      game->bi = ft_strlen(l);

    game->wvalue = 30;
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
        while ((l[(int)p.x] == '1' ||l[(int)p.x] == 's'||l[(int)p.x] == '2')&& 
        l[(int)p.x - 1] != '1' && l[(int)p.x - 1] != '2')
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

                   game->walls.push(&(game->walls),new_wall(new_vector_pointer((start.x ) * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((p.x)* game->wvalue ,(p.y )*game->hvalue),1), sizeof(t_wall));
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
    float size;
    t_sp_texture *tex;


    while (y < this->lines.index)
    {
        x = 0;
        l = this->lines.get(&this->lines , y);
        while (l[x] != '\0')
        {
          size = game->hvalue;
            if (ft_strchr("12s5", l[x]) == NULL)
            {
                tex = get_sp_tex(l[x] - 48);
                if (tex != NULL)
                {
                  if (tex->wsize < size)
                    size = tex->wsize;

                game->sprites.push(&game->sprites, 
                new_sprite(new_vector_pointer((x + 0.5) * game->wvalue,
                 (y + 0.5) * game->hvalue), size * 0.5, l[x] - 48),sizeof(t_sprites));
                }
            }
            else if (l[x] == '5')
                {
                    tex = get_sp_tex( l[x] - 48);
                  if (tex != NULL)
                  {
                    game->lights.push(&game->lights, 
                    new_sprite(new_vector_pointer((x + 0.5) * game->wvalue,
                    (y + 0.5) * game->hvalue), 0.19 * game->hvalue  , l[x] - 48),sizeof(t_sprites));
                  }
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
  
    game->hvalue = 64;
    this->lines.foreach(&(this->lines),&get_w);
    game->wvalue = 64;
    get_walls(this);
    get_sprites(this);
    return TRUE;
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
  game->color[4] = 0xbb3b0e;
  game->color[5] = 0x2c786c;
}
void parse_properties(t_parser *this)
{
  t_token *token;

  if (this == NULL || this->tokens.arr == NULL)
    put_error(game ,ft_strdup("no map!"));
  else{
    token = get_token_by_key(this, "R");
    parse_resultion(this ,token);
    #ifndef BONUS
    token = get_token_by_key(this, "S");
    parse_sprite(this , token);
    #else
    parse_sprite_bonus(this);
    #endif
    token = get_token_by_key(this, "C");
    parse_ceil(this, token);
    token = get_token_by_key(this, "F");
    parse_floor(this, token);
    token = get_token_by_key(this, "SE");
    parse_se_tex(this , token);
    token = get_token_by_key(this, "WE");
    parse_we_tex(this , token);
    token = get_token_by_key(this, "EA");
    parse_ea_tex(this , token);
    token = get_token_by_key(this, "SO");
    parse_so_tex(this , token);
    
  }
}

void   parser_do_final(t_parser *this)
{
    char *line;

    game = this->g_p;
    this->get_lines(this);
    this->parse_file(this);
    init_tex();
    if (game->errors.index > 0)
      return;
    parse_properties(this->tokens);
}