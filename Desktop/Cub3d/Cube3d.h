# ifndef FT_CUB_H
# define FT_CUB_H
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
typedef int  t_bool;
#define TRUE 1
#define FALSE 0


typedef struct s_vector{
    float x;
    float y;
    float len;

    float (*length)(struct s_vector *this);
    void (*add)(struct s_vector *this , struct s_vector *o);
    void (*sub)(struct s_vector *this, struct s_vector *o);
    int (*compare_to)(void  *this , void *o);
}              t_vector;
/* reg datatype 1  2-char  3-s_vector 4  */
typedef struct s_array_list{
        void **arr;
        size_t index;
        size_t length;
        size_t size_of_object;
        size_t data_type;
        t_bool (*push)(struct s_array_list *this, void *value ,size_t size_of_item);
        void *(*get)(struct s_array_list *this, size_t index);
        t_bool (*check_size)(struct s_array_list *this);
        t_bool (*check_data_type)(struct s_array_list *this, void *value, size_t size_of_item);
        t_bool (*new_array_double_size)(struct s_array_list *this);
        void (*foreach)(struct s_array_list *this ,void (*f)(void *item));
        void (*delete_if)(struct s_array_list *this, t_bool(*cond)(void *item),void (*fe)(void *item));
        void (*sort)(struct s_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r);
        void (*_free)(struct s_array_list *this , void (*fe)(void *item));
        t_bool (*update_at)(struct s_array_list *this, void *value, size_t index);
        void (*swap)(void **a, void **b);

}               t_array_list;

typedef struct s_player{
    t_vector    pos;
    float       rotaion_angle;
    

}       t_player;


/*  Vector  functions */
t_vector new_vector(t_vector *this,  float x, float y);
float length(t_vector *this);
void add(t_vector *this , t_vector *o);
void sub(t_vector *this, t_vector *o);

int compare_to(void  *this , void *o);

/*   arraylist functions */
t_array_list *new_array_list(t_array_list *this, size_t first_size, size_t __sizeofit, size_t data_type);
t_bool push(t_array_list *this, void *value, size_t size_of_item);
void *get(t_array_list *this, size_t  index);
t_bool check_size(t_array_list *this);
t_bool check_data_type(t_array_list *this, void *value, size_t size_of_item);
t_bool new_array_double_size(t_array_list *this);
void foreach(t_array_list *this ,void (*f)(void *item));
void delete_if(t_array_list *this, t_bool(*cond)(void *item), void (*fe)(void *item));
void sort(t_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r);
void _free(t_array_list *this, void (*fe)(void *item));
void ft_swap(void **a, void **b);
t_bool update_at(struct s_array_list *this, void *value, size_t index);

# endif