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
        words->push(words,ft_strdup("S"),sizeof(char *));
        words->push(words,ft_strdup("F"),sizeof(char *));
        words->push(words,ft_strdup("C"),sizeof(char *));
        words->push(words,ft_strdup("MAP"),sizeof(char *));
    }
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
        if (!map_created() && !is_empty_or_comment(line) && !create_map(line))
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
    }else 
        put_error(parser->g,ft_strjoin("propeties after map line :\n", line));
    }
}

t_bool create_map(char *line)
{
    t_bool is_map_l;
    int i;

    i = 0;
    is_map_l = TRUE;
    if (line == NULL)
        return FALSE;
    
    return  is_map_line;
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
    if(ch == '\0')
        return (FALSE);
    if (ft_strchr("0123456789SNWEs",ch) != NULL)
        return (TRUE);
    return (FALSE);
}
t_bool map_created(){
    size_t i;
    t_token *token;
    i = 0;
    while ( i < this->tokens.index)
    {
        token = this->tokens.get(&(this->tokens), i);
        if (ft_strncmp(token->token , "MAP", 3) == 0)
         return (TRUE);
        i++;
    }
    return (FALSE);
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