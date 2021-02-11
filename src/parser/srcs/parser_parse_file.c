/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:45:41 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:48 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
t_parser *parser;

t_array_list *keywords;

void parser_parse_file(t_parser *this)
{
	if(this != NULL && this->lines.arr != NULL && this->tokens.arr != NULL)
	{
		parser = this;

		keywords  = (t_array_list *) malloc(sizeof(t_array_list));
		new_array_list(keywords,7 ,sizeof(char *));
		init_properties(keywords);
		this->lines.foreach(&(this->lines), &parse_token);
		verify_map(parser);
		keywords->free(keywords,&free);
	}
}

void init_properties(t_array_list *words)
{
	if(words !=NULL && words->arr != NULL)
	{
		words->push(words,ft_strdup("R"),  sizeof(char *));
		words->push(words,ft_strdup("NO"),sizeof(char *));
		words->push(words,ft_strdup("SO"),sizeof(char *));
		words->push(words,ft_strdup("WE"),sizeof(char *));
		words->push(words,ft_strdup("EA"),sizeof(char *));
		words->push(words,ft_strdup("F"),sizeof(char *));
		words->push(words,ft_strdup("C"),sizeof(char *));
		words->push(words,ft_strdup("MAP"),sizeof(char *));
#ifdef BONUS
		push_bonus_sprites_properties(words);
#else
		words->push(words,ft_strdup("S"),sizeof(char *));
#endif
	}
}
void push_bonus_sprites_properties(t_array_list *words)
{
	int i;

	i = 0;
	while (i <= 9)
	{
		words->push(words, ft_itoa(i), sizeof(char *));
		i++;
	}
}
void put_token(t_parser *p , t_array_list word)
{
	t_token *token;
	if (get_token_by_key(p, (char *) word.get(&word,0)) == NULL){
		token = (t_token *) malloc(sizeof(t_token));

		new_token(token, word);
		p->tokens.push(&(p->tokens),token , sizeof(t_token *));
	}
	else 
		put_error(p->g, ft_strdup("diplicate property "));
}

t_bool map_ended(char *line, t_bool *var)
{


	if( var == NULL)
		*var = FALSE;
	if (map_created() && !is_map_line(line))
		*var = TRUE;
	return *var;
}

void parse_token(void *item)
{
	char *line;
	t_array_list *word;
	static t_bool var;

	if (item != NULL && parser != NULL)
	{
		line = (char *) item;
		if (!map_ended(line , &var) && is_map_line(line) )
			create_map(line);
		else if (!map_created() && !is_empty_or_comment(line))
		{
			word = ft_split_property(line);
			if (word != NULL && word->index >1)
			{
				if(!check_properties(word->get(word, 0)))
					put_error(parser->g,ft_strjoin("invalid line :\n", line));
				else 
					put_token(parser , *word);
			}else
				put_error(parser->g,ft_strjoin("invalid line :\n", line));
		}
		else if(((map_created() || map_ended(line, &var )) && !ft_is_empty(line)))
			put_error(parser->g,ft_strjoin("propeties after map line :\n", line));
	}
}

t_bool create_map(char *line)
{
	t_token *token;
	if (line == NULL)
		return FALSE;
	if(map_created())
		token = get_token_by_key(parser , "MAP");
	else
	{
		token = (t_token *) malloc(sizeof(t_token ));
		new_empty_token(token,ft_strdup("MAP"));
		if(token != NULL)
			parser->tokens.push(&(parser->tokens),token,sizeof(t_token *));
	}
	if(token == NULL)
		return (FALSE);
	token_push_value(token , line);
	return  (TRUE);
}

t_bool is_map_line(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return FALSE;
	if(line[0] == '\0' || ft_is_empty(line))
		return (FALSE);
	while (ft_iswhitespace(line[i]))
		i++;
	while (is_map_character(line[i]))
		i++;
	if(line[i] == '\0')
		return (TRUE);
	return (FALSE);
}
t_bool is_map_character(char ch)
{
	char *arr;

#ifdef BONUS
	arr = "0123456789 SNWEs";
#else
	arr = "012 SNWE";
#endif
	if(ch == '\0')
		return (FALSE);
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}
t_bool map_created(){
	t_token *token;

	token = get_token_by_key(parser ,"MAP");
	return (token == NULL ? FALSE :TRUE);
}

t_bool is_empty_or_comment(char *line){
	int i;
	int len;

	if(line != NULL)
	{
		len = ft_strlen(line);
		i = 0;
		while (ft_iswhitespace(line[i]))
			i++;
#ifdef BONUS
		if(i < len)
			if(line[i] == '#')
				return TRUE;
#endif
		return i == len  && i == 0? TRUE : FALSE;
	}
	else 
		return TRUE;
	return FALSE;
}
t_bool ft_is_empty(char *line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if(line != NULL)
	{
		len = ft_strlen(line);
		while (ft_iswhitespace(line[i]) && line[i] != '\0')
			i++;
	}
	return (len == i ? TRUE : FALSE);
}

t_bool check_properties(char *token)
{

	size_t       index;
	char *key;
	int len1;
	int len2;

	if(token != NULL)
	{
		index = 0;
		while (index < keywords->index)
		{
			key =(char *) keywords->get(keywords ,index);
			len1 = ft_strlen(key);
			len2 = ft_strlen(token);
			if (key != NULL && ft_strncmp(token ,key,( len1 > len2 ? len1 : len2)) == 0)
				return TRUE;
			index++;
		}
	}
	return FALSE;
}
