t_game *game;
void push_n_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_d;
    t_vector start;

    l_d =this->lines.get(&(this->lines),r_p.y + 1);
    game = this->g_p;
    new_vector(&start , r_p.x , r_p.y);
    if (l_d != NULL)
     while (l[(int)r_p.x] != '\0' )
     {
                while ((l[(int) r_p.x] == '1'
                ||l[(int) r_p.x] == 's'||l[(int) r_p.x] == '2')
                 && l_d[(int)r_p.x]!='1' )
                {
                    if ( l[(int) r_p.x] == '\0' || l_d[(int)r_p.x] == '\0')
                        break;
                    r_p.
                     += 1;
                }
                if (start.x < r_p.x)
                            insert_wall(start.x,start.y,r_p.x,r_y);
                 if(l[(int)r_p.x] == 'N' || l[(int)r_p.x] == 'S' 
                 || l[(int)r_p.x] == 'E' || l[(int)r_p.x] == 'W')
                {
                  insert_player(r_p.x, r_p.y)
                    l[(int) r_p.x] = '0';
                }
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;         
        }
}
void insert_wall(double s_x,double s_y,double e_x,double e_y){
    game->walls.push(&(game->walls),
    new_wall(
        new_vector_pointer(s_x * game->wvalue, 
                            (s_y + 1) * game->hvalue),
        new_vector_pointer((e_x )* game->wvalue ,
                        (e_y + 1)*game->hvalue),0),
                        sizeof(t_wall));
}
void insert_player(double x,double y){
    new_player(&(game->player),
                   new_vector_pointer(x *game->wvalue + (0.5 * game->wvalue ),
                    y * game->hvalue + (0.5 *game->hvalue)) ,
                   l[(int)r_p.x]);
}