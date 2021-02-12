/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_foreach.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:37:36 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:37:40 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"

void	foreach(t_array_list *this, void (*f)(void *item))
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

void	ft_swap(void **a, void **b)
{
	void *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
