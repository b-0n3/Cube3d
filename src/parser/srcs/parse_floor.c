#include "parser.h"

void parse_floor(t_parser *this, t_token *token)
{
  #ifdef BONUS
    parse_floor_tex(this->g, token);
  #else
    parse_floor_color(this->g ,token);
  #endif
}

void parse_floor_color(t_game *this, t_token *token)
{
  t_array_list  word;
  char          *line;
  int           color;


  if (this != NULL && token != NULL)
  {
    new_array_list(&word,2,sizeof(char *));
    line = token->get(&(token->values),0);
    if(line == NULL)
      put_error(this,ft_strdup("invalid floor color"));
    split_that(&word, line, ',');
    color = parse_color(this , &word);
    if (color < 0)
      put_error(this,ft_strdup("invalid floor color"));
    else
      this->color[6] = color;
  }
}

void parse_floor_tex(t_game *this, t_token *token)
{
    int fd;
    char *filename;
    
    if (this == NULL || token == NULL)
        return;
    filename =(char *) token->values.pop(&(token->values));
    if(filename != NULL)
        fd = open(filename , O_RDONLY);
    if (filename == NULL || fd < 0)
        put_error(this , ft_strdup("invalid floor texture file"));
    else
    {
        this->floor = new_sp_texture(filename, 10);
        close(fd);
    }
}