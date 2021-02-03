# include "util.h"
# include "game.h"

void    put_error(t_game *g_p, char *message)
{
    g_p->errors.push(&g_p->errors , message,
            sizeof (char *));
}