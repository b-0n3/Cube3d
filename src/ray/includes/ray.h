# ifndef FT_RAY_H
#define FT_RAY_H

#include "vector.h"

typedef struct s_ray{
        t_vector *pos;
        t_vector *dir;
        double   len;
        int     kind;
        double   angle;
        int index;
        int coli;
        void (*update)(struct s_ray *this, double angle, int i);
        void    (*cast)(void *ray);
        void    (*render)(struct s_ray *this);
        double (*length)(struct s_ray *this);
        void (*free)(void *item);
}       t_ray;

typedef struct s_ray_sp{
        t_vector *pos;
        t_vector *dir;
        int     offset;
        int     kind;
        double   angle;
        int index;
        double dist;
        struct s_sptites *sp;
        void    (*cast)(void *ray);
        void    (*render)(struct s_ray_sp *this);
        double (*length)(struct s_ray_sp *this);
        void (*update)(struct s_ray_sp *this, t_vector *dir, struct s_sptites *sp);
        void (*free)(void *item);
} t_ray_sp;

/* ray  function*/
t_ray *new_ray(t_vector *pos, double angle, int i);
void    cast_ray(void *ray);
void    render_ray(t_ray *this);
void update_ray(t_ray *this, double angle, int i);
void free_ray(void *item);
double      ray_len(t_ray *ray);
double      ray_sp_len(t_ray_sp *ray);

t_ray_sp *new_sp_ray(t_vector *pos, t_vector *dir,  double angle, int i,struct s_sptites *sp);
void free_ray_sp(void *item);
void update_sp_ray(t_ray_sp *this, t_vector *dir, struct s_sptites *sp);
int pick_color(int kind, double correctdis);

#endif