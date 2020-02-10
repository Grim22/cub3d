#include "cub.h"
// gerer les cas ou le fichier en input est incorrect
// gerer les conversions depuis/vers float
// free (notamment apres les split)
// ft_scan: attention a preciser la 2em lettre si deux id peuvent avoir la meme

int ft_fill_res(int indice, char *line, t_cord_i *reso)
{
    char **words;
    int i;
    
    words = ft_split(line, ' ');
    reso->x = ft_atoi(words[1]);
    reso->y = ft_atoi(words[2]);
    i = 0;
    while(words[i])
    {
        free(words[i]);
        i++;
    }
    free(words);
    return(0);
}

int ft_scan(char *line)
{
    if(line[0] == '1')
        return(1);
    if(line[0] == 'R')
        return(2);
    return(0);
}

//Valeurs possibles (1, 0):Sud, (-1, 0):Nord, (0, -1):W, (0, 1):E
int set_dir(t_cord_f *dir, char orientation)
{
    if (orientation == 'N')
    {
        dir->x = -1;
        dir->y = 0;
    }
    if (orientation == 'S')
    {
        dir->x = 1;
        dir->y = 0;
    }
    if (orientation == 'W')
    {
        dir->x = 0;
        dir->y = -1;
    }
    if (orientation == 'E')
    {
        dir->x = 0;
        dir->y = 1;
    }
    return(0);
}

int ft_init_parse(int ***map, t_cord_f *pos, t_cord_f *dir, t_cord_i *res, char *filename)
{
    char *line;
    int ret;
    int i;
    int fd;
    t_list *lst;
    
    lst = NULL;

    fd = open(ft_strjoin(filename, ".cub"), O_RDONLY);
    if (fd == -1)
    {
        perror("Error on the first argument");
    }
    while((ret = get_next_line(fd, &line)))
    {
        //printf("line: %s\n", line);
        if (ret == -1)
            return(-1);
        i = ft_scan(line);
        if (i == 1)
            ft_get_map(&lst, line);
        if (i == 2)
            ft_fill_res(i, line, res);
    }
    ft_fill_map(lst, map);
    ft_lstclear(&lst, free);
    ft_fill_dir_pos(pos, dir, *map);
    ft_check_map(*map);
    return (1);
}

int ft_return_error(int err_index)
{
    return(1);
}