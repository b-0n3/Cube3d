#include  "cub3d.h"

t_game *game;

/* 
  @autor b0ne@1337 
  
      
*/






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
    put_error(game ,ft_strdup("empty file!"));
  else{
    token = get_token_by_key(this, "R");
    parse_resultion(this ,token);
    #ifndef BONUS
    token = get_token_by_key(this, "S");
    parse_sprite(this , token, 2);
    #else
    parse_sprite_bonus(this);
    #endif
    token = get_token_by_key(this, "C");
    parse_ceil(this, token);
    token = get_token_by_key(this, "F");
    parse_floor(this, token);
    token = get_token_by_key(this, "NO");
    parse_no_tex(this , token);
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

    game = this->g;
    this->get_lines(this);
    this->parse_file(this);
    init_tex();
    if (game->errors.index > 0)
      return;
    parse_properties(this);
    parse_map(this);
}