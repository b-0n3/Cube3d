#ifndef FT_LINE_H
#define FT_LINE_H
#include "vector.h"

typedef struct s_line {
    t_vector *pos;
    t_vector *dir;
}   t_line;

#endif