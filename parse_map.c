#include "cub.h"

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
            printf("i: %d, j: %d --> %d\n", i, j , (*map)[i][j]);
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

int ft_free_map(int **map)
{
    int i;

    i = 0;
    while((map)[i])
    {
        free((map)[i]);
        i++;
    }
    free(map);
    return(0);
}

void ft_print_map(int **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        printf("%d :", i);
        while(j < 25)
        {
            printf("%d", map[i][j]); 
            j++;
        }
        printf("  len: %d\n", j);
        i++;
    }
}