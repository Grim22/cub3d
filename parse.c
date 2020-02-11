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

int ft_scan_id(char *line)
{
   if(line[0] == 0)
	return(0);
   if(line[0] == '1')
        return(1);
   if (ft_strlen(line) < 2)
	return (-1); 
    if(line[0] == 'R' && line[1] == 32)
        return(2);
    if(line[0] == 'S' && line[1] == 32)
        return(3);
    if(line[0] == 'F' && line[1] == 32)
        return(4);
    if(line[0] == 'C' && line[1] == 32)
        return(5);
    if(line[0] == 'N' && line[1] == 'O')
        return(6);
    if(line[0] == 'S' && line[1] == 'O')
        return(7);
    if(line[0] == 'W' && line[1] == 'E')
        return(8);
    if(line[0] == 'E' && line[1] == 'A')
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
    if(line[0] == 'N' && line[1] == 'O')
        *last = *last | _NO;
    if(line[0] == 'S' && line[1] == 'O')
        *last = *last | _SW;
    if(line[0] == 'W' && line[1] == 'E')
        *last = *last | _WE;
    if(line[0] == 'E' && line[1] == 'A')
        *last = *last | _EA;
}

int ft_scan(char *line)
{
    static unsigned char last;
    static char map_on;
    int ret;

    printf("last: %d\n", last);
    if ((ret = ft_scan_id(line)) == -1)
    {
	ft_putstr_fd("Error\nWrong line:\n", 1);
	ft_putstr_fd(line, 1);
	return(-1);
    }
    printf("ret: %d\n", ret);
    ft_scan_last(line, &last);
    if ((map_on == 0 && ret == 1 && last != 255) || (map_on && (ret != 1 && ret != 0))) // cas 1) la map arrive avant que tous les autres param aient ete donnes cas 2) des param sont donnes en dessous de la map (des doublons): on a commence la map et la ligne nest ni une ligne de map ni la derniere ligne
    {
	ft_putstr_fd("Error\nAll parameters must be given before map: missing parameter OR parameter(s) given after map", 1);
	return(-1);
    }
    if (ret == 1)
	map_on = 1;
    return(ret);
}

int check_filename(char *filename)
{
    char *ext;

    ext = ft_substr(filename, ft_strlen(filename) - 4, ft_strlen(filename));
    printf("ext: %s\n", ext);
    if (ft_strncmp(ext, ".cub", 4))
        return(-1);
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
    if (check_filename(filename) == -1)
    {
	ft_putstr_fd("Error\nFile extension must be .cub", 1);
	return(-1);
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nWrong argument: filename");
        return(-1);
    }
    while((ret = get_next_line(fd, &line)))
    {
        printf("Line: %s\n", line);
	//printf("line[0]: %d\n", line[0]);
	if (ret == -1)
            return(-1);
        if ((i = ft_scan(line)) == -1)
	    return(-1);
        if (i == 1)
            ft_lstadd_back(&lst, ft_lstnew(line));
        else if (i == 2)
        {
            ft_fill_res(i, line, res);
            free(line);
        }
        /*else if (i > 9)
        {
            ft_putstr_fd("Error\nWrong line in .cub file: ", 1);
            ft_putstr_fd(line, 1);
            free(line);
            return(-1);
        }*/
    }
    ft_fill_map(lst, map);
    ft_lstclear(&lst, &free);
    ft_fill_dir_pos(pos, dir, *map);
    if (ft_check_map(*map) == -1) // verifier egalement quon a bien recu une map (si on a la map cest quon a aussi eu tous les autres param)
        return(-1);
    return (1);
}
