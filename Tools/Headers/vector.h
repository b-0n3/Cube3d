#ifndef FT_VECTOR_H
#define FT_VECTOR_h

typedef struct s_vector{
    double x;
    double y;
    double len;

    double (*length)(struct s_vector *this);
    void (*add)(struct s_vector *this , struct s_vector *o);
    void (*sub)(struct s_vector *this, struct s_vector *o);
    int (*compare_to)(void  *this , void *o);
    struct s_vector *(*get_dir_angle)(struct s_vector *this , double angle);
    void (*to_string)(void *item);
}              t_vector;


t_vector new_vector(t_vector *this,  double x, double y);
t_vector *new_vector_pointer(double x, double y);
t_vector *dir_from_angle(t_vector *this, double angle);
double length(t_vector *this);
void add(t_vector *this , t_vector *o);
void sub(t_vector *this, t_vector *o);
int compare_to(void  *this , void *o);
void vector_to_string(void *item);
double  normelize_angel(double angle);

#endif