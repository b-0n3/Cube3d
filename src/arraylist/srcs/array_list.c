/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:37:36 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:37:40 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"

/*
***  @param first_size : array initial size
***  @param __sizeofit : sizeof element
***  @ param this :  ! please make sure the pointer you passing is already
***               allocated or expect a  bus error
*/

t_array_list	*new_array_list(
					t_array_list *this, size_t first_size, size_t sizeofit)
{
	this->arr = (void *)malloc(first_size * sizeofit);
	if (this->arr != NULL)
	{
		this->index = 0;
		this->length = first_size;
		this->size_of_object = sizeofit;
		this->push = &push;
		this->get = &get;
		this->check_size = &check_size;
		this->check_data_type = &check_data_type;
		this->new_array_double_size = &new_array_double_size;
		this->foreach = &foreach;
		this->delete_if = &delete_if;
		this->sort = &sort;
		this->free = &array_list_free;
		this->update_at = &update_at;
		this->swap = &ft_swap;
		this->pull = &pull;
		this->pull_i = &pull_index;
		this->filter = &filter_list;
		return (this);
	}
	return (NULL);
}
