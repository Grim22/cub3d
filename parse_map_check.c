/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:08 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/12 16:14:09 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_convert_maptoint(char **map)
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
}

int ft_check_mapborders(char **map)
{
    int i;
    int j;
    
    i = 0;
    while(map[i]) // check des 1 en fin et debut de ligne
    {
        j = 0;
        while(map[i][j])
            j++;
        if (map[i][j - 1] != '1') // on sait la ligne fait au moins un char (celui quon a scanne)
            return(-1);
        i++;
    }
    j = 0; 
    while(map[0][j]) // check des 1 sur la premiere et derniere ligne
    {
        if (map[0][j] != '1')
            return(-1);
        j++;
    }
    j = 0;
    while(map[i - 1][j])
    {
        if (map[i - 1][j] != '1') // on sait qu'il y a au moins une ligne (sinon erreur: no map)
            return(-1);
        j++;
    }
    return(0);
}

int ft_check_mapcars(char **map)
{
    int i;
    int j;
    
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] != 48 && map[i][j] != 49 && map[i][j] != 50 && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
                return(-1);
            j++;
        }
        i++;
    }
    return(0);
}

int ft_check_mapdir(char **map)
{
    int i;
    int j;
    int dir;
    
    i = 0;
    dir = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                dir = dir + 1;
            j++;
        }
        i++;
    }
    if (dir != 1)
        return(-1);
    return(0);
}

int ft_check_map(char **map)
{
    if (ft_check_mapdir(map) == -1)
    {
        ft_putstr_fd("Error\nPlease specify one (and only one) direction on the map: N, E, W or S", 1);
        return(-1); // si pas de direction ou plusieurs
    }
    if (ft_check_mapcars(map) == -1)
    {
        ft_putstr_fd("Error\nWrong char on map", 1);
        return(-1); // si caracteres non autorises dans la map
    } 
    if (ft_check_mapborders(map) == -1)
    {
        ft_putstr_fd("Error\nBorders should be only '1'", 1);
        return(-1); // si pas un 1 en fin ou debut de ligne
    }
    return(0);
}