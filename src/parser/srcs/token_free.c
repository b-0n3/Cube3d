#include "cub3d.h"

void free_token(void *item)
{
    t_token *this = (t_token *) item;

    if (this != NULL)
    {
        if (this->token!= NULL)
            free(this->token);
        if (this->values.arr != NULL)
            this->values.free(&this->values, &free);
        free(this);
    }
}