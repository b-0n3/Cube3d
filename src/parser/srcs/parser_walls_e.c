t_game *game;
void push_e_walls(t_vector p)
{
    char *l;
    t_vector start;
    int len;
    l = game->parser->lines.get(&game->parser->lines, p.y);
    new_vector(&start , p.x, p.y);

    double y = p.y;
    while (l != NULL && p.y < game->parser->lines.index)
    {
         l = game->parser->lines.get(&game->parser->lines, p.y);
        while ((l[(int)p.x] == '1' || l[(int)p.x] == 's'|| l[(int)p.x] == '2')
         && l[(int)p.x + 1] != '1' && l[(int)p.x + 1] != '2')
        {
            p.y += 1;
            l = game->parser->lines.get(&game->parser->lines, p.y);
            if (l == NULL  || ft_strlen(l) <= p.x)
                break;

        }

            if (start.y < p.y)
               
                 p.y += 1;
                 start.x = p.x;
                 start.y = p.y;
    }
}
void insert_e_wall(

)
{
        game->walls.push(&(game->walls),
        new_wall(new_vector_pointer((start.x +1 ) * game->wvalue,
         (start.y )*game->hvalue),
         new_vector_pointer((p.x + 1)* game->wvalue ,
         (p.y )*game->hvalue),3), sizeof(t_wall));
             
}