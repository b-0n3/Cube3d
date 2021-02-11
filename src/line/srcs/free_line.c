#include "cub3d.h"

void free_line(t_line this){
    if (this.dir != NULL)
        free(this.dir);
}