/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/19 15:28:27 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_fill_map(t_list *lst, char ***map)
{
    int i;
    int j;
    char *c;
    int len;
    
    *map = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
    i = 0;
    while(lst)
    {
        c = ft_str_delchar(lst->content, ' ');
        len = 0;
        while(c[len])
            len++;
        (*map)[i] = malloc((len + 1) * sizeof(char));
        j = 0;
        while(j < len)
        {
            (*map)[i][j] = c[j];
            j++;
        }
        (*map)[i][j] = 0;
        lst = lst->next;
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

int ft_fill_dir_pos(t_cord_f *pos, t_cord_f *dir, char **map)
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

int ft_fill_plane(t_cord_f *plane, t_cord_f dir)
{
    // determination du vecteur plan image:
        // dir: perpendiculaire a direction du joueur = dir.
        // valeur: plane / 2
    
    int bool_x = 0;
    int bool_y = 0;
    
    if (dir.x)
        bool_y = 1;
    else
        bool_x = 1;
    plane->x = bool_x * tan(FOV/2);
    plane->y = bool_y * tan(FOV/2);
    return(0);
}

int ft_fill_check_map(t_list **lst, char ***map, t_param *params)
{
    if (*lst == NULL)
    {
	    ft_putstr_fd("Error\nNo map", 1);
	    return(-1);
    }
    ft_fill_map(*lst, map);
    ft_lstclear(lst, &free);
    if (ft_check_map(*map) == -1) 
        return(-1);
    ft_fill_dir_pos(&(params->pos), &(params->dir), *map);
    ft_fill_plane(&(params->plane), params->dir);
    return(0);
}



void ft_print_map(char **map)
{
    int i;
    int j;

    printf("Hello\n");
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            printf("%c", map[i][j]); 
            j++;
        }
        printf("  len: %d\n", j);
        i++;
    }
}
