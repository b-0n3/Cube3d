#include "array_list.h"
/*
   @autor b0n3@1337
   */
t_bool update_at(t_array_list *this, void *value, size_t index)
{

	if(index <= this->index)
	{
		this->arr[index] = value;
		return TRUE;
	}
	return FALSE;
}


void *get(t_array_list *this, size_t index)
{
	if (this->index > index && index >= 0)
		return  this->arr[index];
	return NULL;
}

void _free(t_array_list *this, void (*fe)(void *item))
{
	if (this != NULL && fe != NULL)
		this->foreach(this, fe); 
	this->index = 0;

	free(this->arr);     
}
