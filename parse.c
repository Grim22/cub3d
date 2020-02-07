#include "cub.h"
#include "libft.h"
// gerer les cas ou le fichier en input est incorrect
// gerer les conversions depuis/vers float
// free (notamment apres les split)
// ft_scan: attention a preciser la 2em lettre si deux id peuvent avoir la meme



int ft_get_map(t_list **lst, char *line)
{
    ft_lstadd_back(lst, ft_lstnew(line));
    return(1);
}

int ft_fill_res(int indice, char *line, t_cord_i *reso)
{
    char **words;
    
    words = ft_split(line, ' ');
    reso->x = ft_atoi(words[1]);
    reso->y = ft_atoi(words[2]);
    // faire les free
    return(0);
}

int ft_scan(char *line)
{
    if(line[0] == '1')
        return(1);
    if(line[0] == 'R')
        return(2);
    /*if(line[0] == 'A')
        return(2);
    if(line[0] == 'c' && line[1] == ' ')
        return(3);
    if(line[0] == 'l')
        return(4);
    if(ft_len(line) > 1 && line[0] == 's' && line[1] == 'p')
        return(5); 
    */
    return(0);
}

int ft_fill_map(t_list *lst, int ***map)
{
    int i;
    int j;
    char **c;
    int len;
    
    *map = malloc((ft_lstsize(lst) + 1) * sizeof(int *));
    i = 0;
    while(lst)
    {
        c = ft_split(lst->content, ' ');
        len = 0;
        while(c[len])
            len++;
        (*map)[i] = malloc((len + 1) * sizeof(int));
        j = 0;
        while(j < len)
        {
            (*map)[i][j] = c[j][0];
            free(c[j]);
            j++;
        }
        (*map)[i][j] = 0;
        lst = lst->next;
        free(c);
        i++;
    }
    (*map)[i] = 0;
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

int ft_fill_dir_pos(t_cord_f *pos, t_cord_f *dir, int **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                pos->x = i;
                pos->y = j;
                set_dir(dir, (char)map[i][j]);
            }
            j++;
        }
        i++;
    }
    return(0);
}

int ft_init_parse(int ***map, t_cord_f *pos, t_cord_f *dir, t_cord_i *res)
{
    char *line;
    int ret;
    int i;
    int fd;
    t_list *lst;
    
    lst = NULL;

    fd = open("test.cub", O_RDONLY);

    while((ret = get_next_line(fd, &line)))
    {
        if (ret == -1)
            return(-1);
        i = ft_scan(line);
        if (i == 1)
            ft_get_map(&lst, line);
        if (i == 2)
            ft_fill_res(i, line, res);
    }
    if (ret == -1)
        return(-1);
    i = ft_scan(line);
    if (i == 1)
        ft_get_map(&lst, line);
    if (i == 2)
        ft_fill_res(i, line, res);
    ft_fill_map(lst, map);
    ft_fill_dir_pos(pos, dir, *map);
    /*
    i = 0;
    while((*map)[11][i])
    {
        printf("map 0: %d\n", (*map)[11][i]);
        i++;
    }*/
    return (1);
}

int ft_return_error(int err_index)
{
    printf("Error\n");
    return(1);
}