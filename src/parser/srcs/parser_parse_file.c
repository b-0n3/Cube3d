#include "parser.h"
t_parser *parser;
t_array_list *keywords;

void parser_parse_file(t_parser *this)
{
    if(this != NULL && this->lines.arr != NULL && this->tokens.arr != NULL)
    {
        parser = this;

        
        new_array_list(keywods,1 ,sizeof(char *));
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
        words->push(words,ft_strdup("R"),sizeof(char *));
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

    i = 1;
    while (i++ <= 9)
        words->push(words, ft_itoa(i), sizeof(char *));
}
void put_token(t_parser *p , t_array_list word)
{
    t_token *token;

    token = (t_token *) malloc(sizeof(t_token));
    new_token(token, word);
}

void parse_token(void *item)
{
    char *line;
    t_array_list *word;
    

    if (item != NULL && parser != NULL)
    {
        line = (char *) item;
        if (is_map_line(line))
            create_map(line);
        else if (!is_empty_or_comment(line))
        {
            word = ft_split_property(line);
            if (word != NULL && word->index >1)
            {
                if(!check_properties(word.get(&word, 0)))
                    put_error(parser->g,ft_strjoin("invalid line :\n", line));
                else 
                    put_token(this , word);
            }else
                put_error(parser->g,ft_strjoin("invalid line :\n", line));
                 word.free(&word, &free);
        }
        else if(map_created())
            put_error(parser->g,ft_strjoin("propeties after map line :\n", line));
    }
}

t_bool create_map(char *line)
{
    t_token *token;
    if (line == NULL)
        return FALSE;
    if(!map_created())
        token = get_token_by_key(parser , "MAP");
    else
    {
        token = new_empty_token(token,ft_strdup("MAP"));
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
    while (ft_iswhitespace(line[i]))
            i++;
    while (is_map_character(line[i]))
        i++;
    if(i == ft_strlen(line))
        return (TRUE);
    retrn (FALSE);
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
    if (ft_strchr(arr,ch) != NULL)
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
        if(i < len)
            if(line[i] == '#')
                return TRUE;
        return i == len ? TRUE : FALSE;
    }
    else 
        return TRUE;
    return FALSE;
}

t_bool check_properties(char *token)
{
    
    size_t       index;
    char *key;
    if(line != NULL)
    {
        
        while (index++ < keywords->index)
        {
            key = keywords->get(keyword ,index)
            if (key != NULL && ft_strncmp(token ,key,ft_strlen(key)) == 0)
                return TRUE;
        }
    }
    return FALSE;
}