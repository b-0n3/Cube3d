#include "Cube3d.h"

t_array_list *new_array_list(t_array_list *this, size_t first_size, size_t __sizeofit)
{
		this->arr = (void *)malloc ( first_size * __sizeofit);
		if (this->arr != NULL)
		{
				this->index = 0;
				this->length = first_size;
				this->size_of_object = __sizeofit;
				this->push = &push;
				this->get = &get;
				this->check_size = &check_size;
				this->check_data_type = &check_data_type;
				this->new_array_double_size = &new_array_double_size;
				this->foreach = &foreach;
				this->delete_if = &delete_if;
				this->sort = &sort;
				this->free = &_free;
				this->update_at = &update_at;   
				this->swap = &ft_swap;
				this->pull = &pull;
				return this;
		}
		return NULL;
}

t_bool push(t_array_list *this, void *value, size_t size_of_item)
{
		if (this != NULL)
		{
				if(this->check_data_type(this, value, size_of_item))
				{
						if (this->check_size(this))
						{
								//this->arr[this->index] = (void *) malloc (this->size_of_object);
								//memcpy((this->arr[this->index]) ,  value , this->size_of_object);
								this->arr[this->index] = value;
								this->index++;
								return TRUE;
						}
						else if (this->new_array_double_size(this))
						{
							 // this->arr[this->index] = (void *) malloc (this->size_of_object);
								//memcpy(this->arr[this->index] ,  value , this->size_of_object);
								this->arr[this->index] = value;
								this->index++;
								return TRUE;
						}
				}
		}
		return FALSE;
}

void *get(t_array_list *this, size_t index)
{
		if (this->index > index && index >= 0)
				return  this->arr[index];
		return NULL;
}

t_bool check_size(t_array_list *this)
{
		if (this != NULL)
		{
				if (this->index < this->length)
						return TRUE;
		}
		return FALSE;
}

t_bool check_data_type(t_array_list *this, void *value, size_t size_of_item)
{
		if (this != NULL)
		{
				if ( size_of_item == this->size_of_object)
						return TRUE;
		}
		return FALSE;
}

t_bool new_array_double_size(t_array_list *this)
{
		if (this != NULL)
		{
				if (this->check_size(this))
						return TRUE;
				else
				{
						size_t ll = this->length;
						this->length *= 2;
						if ((this->length / 2) == ll)
						{
								void **arrr = malloc(this->length * this->size_of_object);
								size_t i = 0;
								while (i < this->index)
								{
										arrr[i] =  this->arr[i];//(void *) malloc (this->size_of_object);
										//memcpy(arrr[i] , this->arr[i],this->size_of_object);
										i++;
								}
								//free(this->arr);
								free(this->arr );
								this->arr = arrr;
								return TRUE;
						}
				}
		}
		return FALSE;
}

void foreach(t_array_list *this ,void (*f)(void *item))
{
		size_t i;
		
		i = 0;
		while (i < this->index)
		{
				if (this->arr[i] != NULL)
						f(this->arr[i]);
						i++;
		}
}

void delete_if(t_array_list *this, t_bool(*cond)(void *item), void (*fe)(void *item))
{
		size_t i;
		size_t x;

		i = 0;
		x =0;

		size_t ixx = 0;
		while (i < this->index)
		{
				x = i + 1;
				if (cond(this->arr[i]))
				{
						if (fe != NULL)
								fe(this->arr[i]);
						while (x < this->index)
						{
								if(!cond(this->arr[x]))
								{  
										this->swap(&(this->arr[i]), &(this->arr[x]));
										break;
								}
								x++;
						}
				}
				i++;
		}
		i = 0;
		while (i < this->index)
		{
				if (!cond(this->arr[i]))
						ixx++;
				i++;
		}
		this->index = ixx  + 1;
		while(ixx < this->length)
		{
				if (fe != NULL)
				fe(this->arr[ixx]);
				this->arr[ixx] = NULL;
				ixx++;
		}
}

int  partition (t_array_list *this, int  low, int  high, int (*cond)(void *item1, void *item2)) 
{ 
		void *pivot = this->arr[high];    
		int i;
		int  j;
		i = (low - 1) ;  
		j = low ;

		while (j <= high - 1) 
		{ 
				if (cond(this->arr[j] , pivot) == 1) 
				{ 
						i++;   
					 this->swap(&(this->arr[i]),&(this->arr[j])); 
				} 
				j++;
		} 
		this->swap(&(this->arr[i + 1]), &(this->arr[high])); 
		return (i + 1); 
} 

void sort(t_array_list *this, int (*cond)(void *item1 , void *item2), int  l, int  r)
{
		if (l < r) 
		{ 
				int pi = partition(this, l, r, cond);
				this->sort(this ,cond, l , (pi - 1)); 
				this->sort(this,cond, (pi + 1) , r ); 
		} 

}

t_bool update_at(t_array_list *this, void *value, size_t index)
{
		if(this != NULL)
		{
				if(index <= this->index)
				{
						this->arr[index] = value;
						return TRUE;
				}
		}
		return FALSE;
}
void _free(t_array_list *this, void (*fe)(void *item))
{
		if (this != NULL && fe != NULL)
				this->foreach(this, fe); 
		this->index = 0;
	 
		free(this->arr);     
}

void ft_swap(void **a, void **b)
{
		void *temp;
		temp = *a;
		*a = *b;
		*b = temp;
}

void *pull(t_array_list *this)
{
		void  *ptr;
		int i;

		i = 0;
		ptr = NULL;
		if (this->index > 0)
		{
				ptr = this->get(this,0);
				while (i  < this->index - 1)
				{
						this->update_at(this, this->get(this ,i + 1), i);
						i++;
				}
				this->index--;
		}
		return ptr;
}