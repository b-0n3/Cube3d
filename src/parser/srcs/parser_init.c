void new_parser(t_parser *this, char *filename, t_game *g_p)
{
    new_array_list(&(this->lines), 7, sizeof(char *));
    this->get_lines = &get_lines;
    this->get_fd = &get_fd;
    this->do_final = &parser_do_final;
    this->free = &free_parser;
    this->g_p = g_p;
    this->fd = this->get_fd(filename);
}

void   free_parser(void *th)
{
    t_parser *this;
    this = (t_parser *) th;
    this->lines.free(&this->lines ,&free);
    free(this);
}