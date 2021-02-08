#include "array_list.h"

t_array_list *filter_list(t_array_list this, size_t size , 
t_bool (*cond)(void *item), void *(*map)(void *item))
{
    t_array_list *list;
    size_t i;
    void  *item;

    list = (t_array_list *) malloc (sizeof(t_array_list));
    new_array_list(list, this.index +1, size);
    i = 0;
    if (  cond != NULL)
    {
        while (i < this.index)
        {
           
            item = this.get(&this, i);
            if (cond(item))
            {
                if (map != NULL)
                    item = map(item);
            list->push(list, item ,size);
            }
            i++;      
        }
    }
    return list;
}