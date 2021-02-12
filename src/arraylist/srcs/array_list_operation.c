/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_operation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:37:04 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:37:13 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"

t_bool	push(t_array_list *this, void *value, size_t size_of_item)
{
	if (this != NULL)
		if (this->check_data_type(this, size_of_item))
		{
			if (this->check_size(this))
			{
				this->arr[this->index] = value;
				this->index++;
				return (TRUE);
			}
			else if (this->new_array_double_size(this))
			{
				this->arr[this->index] = value;
				this->index++;
				return (TRUE);
			}
		}
	return (FALSE);
}

t_bool	check_data_type(t_array_list *this, size_t size_of_item)
{
	if (this != NULL)
	{
		if (size_of_item == this->size_of_object)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	check_size(t_array_list *this)
{
	if (this != NULL)
	{
		if (this->index < this->length)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	new_array_double_size(t_array_list *this)
{
	size_t	i;
	void	**arrr;

	if (this != NULL)
	{
		if (this->check_size(this))
			return (TRUE);
		else
		{
			this->length *= 2;
			arrr = malloc(this->length * this->size_of_object);
			i = 0;
			while (i < this->index)
			{
				arrr[i] = this->arr[i];
				i++;
			}
			free(this->arr);
			this->arr = arrr;
			return (TRUE);
		}
	}
	return (FALSE);
}

void	*pull(t_array_list *this)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = NULL;
	if (this->index > 0)
	{
		ptr = this->get(this, 0);
		while (i < this->index - 1)
		{
			this->update_at(this, this->get(this, i + 1), i);
			i++;
		}
		this->index--;
	}
	return (ptr);
}
