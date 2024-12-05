#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
}

void    check_line(t_game *game, char *line)
{
    int i = 0;
            ft_printf("check_line\n");

    while (i < ft_strlen(line))
    {
        if(line[i] == 'P')
            game->map.players++;
        else if(line[i] == 'E')
            game->map.exits++;
        else if(line[i] == 'C')
            game->map.collectibles++;
        else if(line[i] != '0' && line[i] != '1')
        {
                        ft_printf("not 0 or 1\n");

            exit(-1);
        }
    }
}

void init_map(t_game *game)
{
    game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
    game->map.rows = 0;
    game->map.cols = 0;
}

void	read_map(int fd, t_game *game)
{
    char *line;
    int i;

    ft_printf("reading map %d\n", fd);
    i = 0;
    while (1)
    {
        line = get_next_line(fd);
        ft_printf("%s", line);
        if(i == 0)
            game->map.cols = ft_strlen(line);
        else if(ft_strlen(line) != game->map.cols)
        {
            free_map(game);
            exit(-1);
        }
        else
        {
            ft_printf("hiii\n");
///PLEASE MALLOC
            game->map.map[i] = line;
            game->map.rows++;
            check_line(game, line);
        }
        if(!line)
            break;
        free(line);
        i++;
    }
}
