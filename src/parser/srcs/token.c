/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:47:00 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:47:01 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void new_token(t_token *this, t_array_list list)
{
	if (this != NULL && list.arr != NULL )
	{
		this->token = ft_strdup(list.pull(&list));
		this->free = &free_token;
		new_array_list(&(this->values), 1,sizeof(char *));
		token_push_values(this, list);
	}
}

void new_empty_token(t_token *this, char *token)
{
	if (this != NULL && token != NULL )
	{
		this->token = token;
		this->free = &free_token;
		new_array_list(&(this->values), 1, sizeof(char *));
	}
}

t_bool token_push_values(t_token *this,t_array_list list)
{
	char *line;


	if(this == NULL || this->values.arr == NULL || list.arr == NULL)
		return (FALSE);

	while ((line = list.pull(&list)) != NULL)
		token_push_value(this,line);
	return (TRUE);
}

t_bool token_push_value(t_token *this,char *line)
{
	if(this == NULL || line == NULL || this->values.arr == NULL)
		return (FALSE);
	return this->values.push(&(this->values),ft_strdup(line) ,sizeof(char *));
}

t_token *get_token_by_key(t_parser *this, char *key){
	size_t index;
	t_token *token;
	int len1;
	int len2;

	index = 0;
	if(this == NULL || key == NULL)
		return (NULL);
	while (index < this->tokens.index)
	{
		token = (t_token *) this->tokens.get(&(this->tokens), index);
		len1 = ft_strlen(key);
		len2 = ft_strlen(token->token);
		if(token != NULL && ft_strncmp(token->token , key ,( len1 > len2?len1:len2)) == 0)
			return token;
		index++;
	}
	return (NULL);
}
