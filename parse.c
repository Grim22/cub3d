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

int ft_init_parse(int ***map, t_cord_f *pos, t_cord_f *dir, t_cord_i *res, char *filename)
{
    char *line;
    int ret;
    int i;
    int fd;
    t_list *lst;
    
    lst = NULL;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error on the first argument");
        return(-1);
    }
    while((ret = get_next_line(fd, &line)))
    {
        if (ret == -1)
            return(-1);
        i = ft_scan(line);
        if (i == 1)
            ft_lstadd_back(&lst, ft_lstnew(line));
        else if (i == 2)
        {
            ft_fill_res(i, line, res);
            free(line);
        }
        else
        {
            ft_putstr_fd("Wrong line in .cub file: ", 1);
            ft_putstr_fd(line, 1);
            free(line);
            return(-1);
        }
    }
    ft_fill_map(lst, map);
    ft_lstclear(&lst, &free);
    ft_fill_dir_pos(pos, dir, *map);
    if (ft_check_map(*map) == -1)
        return(-1);
    return (1);
}