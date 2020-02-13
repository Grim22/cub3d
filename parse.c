/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:28 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 12:49:52 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_scan_id(char *line)
{
    if(line[0] == 0)
        return(0);
    if(line[0] == '1')
        return(1);
    if (ft_strlen(line) < 3)
	    return (-1); 
    if(line[0] == 'R' && line[1] == 32)
        return(2);
    if(line[0] == 'S' && line[1] == 32)
        return(5);
    if(line[0] == 'F' && line[1] == 32)
        return(3);
    if(line[0] == 'C' && line[1] == 32)
        return(4);
    if(line[0] == 'N' && line[1] == 'O' && line[2] == 32)
        return(6);
    if(line[0] == 'S' && line[1] == 'O' && line[2] == 32)
        return(7);
    if(line[0] == 'W' && line[1] == 'E' && line[2] == 32)
        return(8);
    if(line[0] == 'E' && line[1] == 'A' && line[2] == 32)
        return(9);
    return(-1);
}

void ft_scan_last(char *line, unsigned char *last)
{   
    if (ft_strlen(line) < 2)
	    return ; 
    if(line[0] == 'R' && line[1] == 32)
        *last = *last | _R;
    if(line[0] == 'S' && line[1] == 32)
        *last = *last | _S;
    if(line[0] == 'F' && line[1] == 32)
        *last = *last | _F;
    if(line[0] == 'C' && line[1] == 32)
        *last = *last | _C;
    if(line[0] == 'N' && line[1] == 'O' && line[2] == 32)
        *last = *last | _NO;
    if(line[0] == 'S' && line[1] == 'O' && line[2] == 32)
        *last = *last | _SO;
    if(line[0] == 'W' && line[1] == 'E' && line[2] == 32)
        *last = *last | _WE;
    if(line[0] == 'E' && line[1] == 'A' && line[2] == 32)
        *last = *last | _EA;
}

int ft_scan_last_error(int ret, int map_on, int last)
{
    if ((map_on == 0 && ret == 1 && last != 255)) 
    // cas 1) la map arrive avant que tous les autres param aient ete donnes 
    {
	    ft_putstr_fd("Error\nAll parameters must be given before map", 1);
	    return(-1);
    }
    if (map_on && ret != 1 && ret) 
    // cas 2) des param sont donnes en dessous de la map (en doublons donc): on a commence la map et la ligne nest ni une ligne de map ni une ligne vide
    {
	    ft_putstr_fd("Error\nParameter(s) given after map", 1);
	    return(-1);
    }
    if (map_on && ret == 0) 
    // cas 3) lignes vides dans la map
    {
	    ft_putstr_fd("Error\nEmpty line in map or after map", 1);
	    return(-1);
    }
    return(0);
}

int ft_scan(char *line)
{
    static unsigned char last;
    static char map_on;
    int ret;

    if ((ret = ft_scan_id(line)) == -1)
    {
	    ft_putstr_fd("Error\nWrong line:\n", 1);
	    ft_putstr_fd(line, 1);
	    return(-1);
    }
    ft_scan_last(line, &last);
    if (ft_scan_last_error(ret, map_on, last) == -1)
        return(-1);
    if (ret == 1)
	    map_on = 1;
    return(ret);
}

int check_filename(char *filename)
{
    char *ext;
    int fd;

    if ((fd = open(filename, O_RDONLY)) == -1)
    {
        perror("Error\nWrong argument: ");
        return(-1);
    }
    ext = ft_substr(filename, ft_strlen(filename) - 4, ft_strlen(filename));
    if (ft_strncmp(ext, ".cub", 4))
	{
        ft_putstr_fd("Error\nFile extension must be .cub", 1);
        return(-1);
    }
    free(ext);
    return(fd);
}

int ft_init_parse(t_param *params, char *filename)
{
    char *line;
    int i;
    int fd;
    t_list *lst;
    
    lst = NULL;
    if ((fd = check_filename(filename)) == -1)
        return(-1);
    while((i = get_next_line(fd, &line)))
    {
        //printf("Line: %d\n", line[0]);
	    if (i == -1 || (i = ft_scan(line)) == -1)
            return(-1);
        if (i == 1)
            ft_lstadd_back(&lst, ft_lstnew(line));
        else if (i) // tout sauf 0, 1 et -1
        {
            if (ft_fill_params(i, line, params) == -1)
                return(-1);
            free(line);
        }
    }
    if (ft_fill_check_map(&lst, &(params->map), params) == -1)
        return(-1);
    return (1);
}
