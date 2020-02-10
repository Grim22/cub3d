#include "cub.h"

int ft_get_map(t_list **lst, char *line)
{
    ft_lstadd_back(lst, ft_lstnew(line));
    return(1);
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
                pos->x = i +0.5;
                pos->y = j + 0.5;
                set_dir(dir, (char)map[i][j]);
            }
            j++;
        }
        i++;
    }
    return(0);
}

int ft_check_map(int **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 48 || map[i][j] == 49 || map[i][j] == 50)
                map[i][j] = map[i][j] - 48;
            j++;
        }
        i++;
    }
    return(0);
}

int ft_free_map(int **map)
{
    int i;

    i = 0;
    while((map)[i])
    {
        //free((map)[i]);
        i++;
    }
    //free(map);
    return(0);
}