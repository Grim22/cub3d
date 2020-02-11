#include "cub.h"

void ft_convert_maptoint(int **map)
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


int ft_check_mapborders(int **map) // ne marche pas car sarrete de boucler quand rencontre un 0 sur la map --> convertir la map en char
// ajouter un check sur les premieres et dernieres lignes de la map (que des 1)
{
    int i;
    int j;
    
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
            j++;
        if (j < 2 || map[i][j - 1] != '1')
            return(-1);
        i++;
    }
    return(0);
}

int ft_check_mapcars(int **map)
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

int ft_check_mapdir(int **map)
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
    //printf("dir: %d\n", dir);
    if (dir != 1)
        return(-1);
    return(0);
}

int ft_check_map(int **map)
{
    if (ft_check_mapdir(map) == -1)
    {
        ft_putstr_fd("Please specify one (and only one) direction on the map: N, E, W or S", 1);
        return(-1); // si pas de direction ou plusieurs
    }
    if (ft_check_mapcars(map) == -1)
    {
        ft_putstr_fd("Wrong char on map", 1);
        return(-1); // si caracteres non autorises dans la map
    } 
    if (ft_check_mapborders(map) == -1)
    {
        ft_putstr_fd("Borders should be '1'", 1);
        return(-1); // si pas un 1 en fin ou debut de ligne
    }
    ft_convert_maptoint(map);
    return(0);
}
