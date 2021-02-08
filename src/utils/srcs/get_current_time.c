#include "cub3d.h"

long long  get_current_time()
{
    struct timeval cur;

    gettimeofday(&cur, NULL);
    return ((long long ) cur.tv_sec * 1000000 + (long long ) cur.tv_usec); 
}