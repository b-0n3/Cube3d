#include "cub3d.h"

t_parser *p;

t_bool is_wall_character(char ch)
{
    char *arr;

    #ifdef BONUS
        arr = " 12";
    #else
        arr = " 1";
    #endif
    if (ft_strchr(arr, ch) != NULL)
        return (TRUE);
    return (FALSE);
}
t_bool check_border_s(t_array_list lines)
{
    char *line;
    int len;
    int i;
    

    if (lines.arr == NULL)
        return (FALSE);
    line = lines.get(&(lines), 0);
    if (line != NULL)
    {
        i = 0;
        len = ft_strlen(line);
        while (i < len && is_wall_character(line[i]))
            i++;
        if (i == len && len != 0)
            return (TRUE);
        put_error(p->g, ft_strjoin("invalid map border\n", line));
    }
    return (FALSE);
}
t_bool check_border_e(t_array_list lines)
{
    char *line;
    int len;
    int i;
    

    if (lines.arr == NULL)
        return (FALSE);
    line = lines.get(&(lines), lines.index -1);
    if (line != NULL)
    {
        i = 0;
        len = ft_strlen(line);
        while (i < len && is_wall_character(line[i]))
            i++;
        if (i == len && len != 0)
            return (TRUE);
        put_error(p->g, ft_strjoin("invalid map border\n", line));
    }
    return (FALSE);
}

t_bool is_map_s_or_end(char ch)
{
    char *arr;

    #ifdef BONUS
        arr = "12";
    #else
        arr = "1";
    #endif
    if (ft_strchr(arr, ch) != NULL)
        return (TRUE);
    return (FALSE);
}

t_bool check_border_i(t_array_list lines, size_t index)
{
    char *line;
    int len;
    int i;
    t_bool ex[2];

    if (index  >= lines.index && index != 0)
        return TRUE;
    line = lines.get(&lines, index);
    if (line != NULL)
    {
        len  = ft_strlen(line)-1;
        while (ft_iswhitespace(line[i]))
            i++;
        while(ft_iswhitespace(line[len]))
            len--;
        if (!is_map_s_or_end(line[i])
         || !is_map_s_or_end(line[len]))
            put_error(p->g, ft_strjoin("invalid line",line));
            return check_border_i(lines, index + 1);
    }
    return (FALSE);
}
t_bool check_borders(t_array_list lines)
{
    return (check_border_e(lines) 
            && check_border_s(lines) 
            && check_border_i(lines, 0));
}

t_bool check_map_char(char ch)
{
    char *arr;

    #ifdef BONUS
        arr = "0123456789NWSE";
    #else
        arr = "012NWSE";
    #endif
     if (ft_strchr(arr, ch) != NULL)
        return (TRUE);
    return (FALSE);
}
void check_sides(char **line, int *len , size_t x){
    int i;

    i = -1;
    while (i < 2)
    {
        if (x + 1 < len[i + 1] && x > 0)
            if (!check_map_char(line[i+1][x + 1])|| !check_map_char(line[i+1][x - 1]))
                put_error(p->g, ft_strjoin("invalid line \n", line[ i + 1]));
        if (x < len[i +1])
            if (!check_map_char(line[i+1][x ]))
                put_error(p->g, ft_strjoin("invalid line \n", line[ i + 1]));
        if (x == len[i + 1] || x - 1 == len[i + 1] || x + 1 == len[i + 1])
          put_error(p->g, ft_strjoin("invalid line \n", line[ i + 1]));
        i++;
    }
}
t_bool check_inside(t_array_list lines, size_t x, size_t y)
{
    char *line[3];
    int i;
    int len[3];
    if (y >= 0 && y >= lines.index)
        return (TRUE);
    i = -1 ;
    while (i < 2)
    {
        line[i + 1] =  lines.get(&lines, y  + i);
        len[i + 1] = line[i + 1] != NULL?ft_strlen(line[i + 1]) : 0;
        i++;
    }
    while (x < len[1])
    {
        if(line[1][x]== '0')
            check_sides(line,len , x);
        x++;
    }

    return check_inside(lines, 0 , y + 1);
}

void verify_map(t_parser *this){
    t_token *token;
    t_array_list lines;



    token = get_token_by_key(this, "MAP");
    if(token == NULL || token->values.arr == NULL || token->values.index <= 0)
       put_error(this->g,ft_strdup("no map!"));
    else
    {
       p = this; 
        lines = token->values;
        if (!( check_borders(lines) && check_inside(lines,0,0)))
            put_error(this->g,ft_strdup("invalid map"));
    }
}
