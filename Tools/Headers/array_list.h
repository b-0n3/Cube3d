#ifndef FT_ARRAY_LIST_H
#define FT_ARRAY_LIST_H

# include <string.h>
# include <stdio.h>

typedef int  t_bool;
#define TRUE 1
#define FALSE 0

typedef struct s_array_list{
        void **arr;
        size_t index;
        size_t length;
        size_t size_of_object;
        t_bool (*push)(struct s_array_list *this, void *value ,size_t size_of_item);
        void *(*get)(struct s_array_list *this, size_t index);
        t_bool (*check_size)(struct s_array_list *this);
        t_bool (*check_data_type)(struct s_array_list *this, void *value, size_t size_of_item);
        t_bool (*new_array_double_size)(struct s_array_list *this);
        void (*foreach)(struct s_array_list *this ,void (*f)(void *item));
        void (*delete_if)(struct s_array_list *this, t_bool(*cond)(void *item),void (*fe)(void *item));
        void (*sort)(struct s_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r);
        void (*free)(struct s_array_list *this , void (*fe)(void *item));
        t_bool (*update_at)(struct s_array_list *this, void *value, size_t index);
        void (*swap)(void **a, void **b);
        void *(*pull)(struct s_array_list *this);

}               t_array_list;


t_array_list *new_array_list(t_array_list *this, size_t first_size, size_t __sizeofit);
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
void *pull(t_array_list *this);

#endif