#ifndef FT_UTILS_H
#define FT_UTILS_H
#include "array_list.h"
#include "libft.h"
#include "game.h"

t_array_list *ft_split_property(char *line);
void put_error(t_game *g_p, char *message);
#endif