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
    ft_printf("check_line %s\n", line);

    game->map.rows++;
    while (i < ft_strlen(line))
    {
        if(ft_strlen(line) != game->map.cols)
            exit(-1);
        if(line[i] == 'P')
            game->map.players++;
        else if(line[i] == 'E')
            game->map.exits++;
        else if(line[i] == 'C')
            game->map.collectibles++;
        else if(line[i] != '0' && line[i] != '1')
        {
            ft_printf("%c not 0 or 1\n", line[i]);
            exit(-1);
        }
		i++;
    }
	ft_printf("line checked");
}

void init_map(t_game *game)
{
    game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
    game->map.rows = 0;
    game->map.cols = 0;
}

// void	read_map(int fd, t_game *game)
// {
//     int i;
// 	char *line;

//     ft_printf("reading map %d\n", fd);
// 	game->map.map = malloc(sizeof(char *) * 100);
//     i = 0;
//     while (1)
//     {
// 		ft_printf("reading ...");
// 		line = get_next_line(fd);
// 		ft_printf("reading 2...");
// 		if(line == NULL)
// 			return;
// 		ft_printf("reading 3...");
//         game->map.map[i] = malloc(ft_strlen(line)*sizeof(char));
// 		game->map.map[i] = line;
//         ft_printf("%d %s", i, game->map.map[i]);
// 		if(ft_strlen(game->map.map[i]) == 0)
//             break;
//         if(i == 0)
//             game->map.cols = ft_strlen(game->map.map[i]);
//         if(ft_strlen(game->map.map[i]) != game->map.cols)
//         {
// 			ft_printf("%s exiting read_map \n", game->map.map[i]);
//             free_map(game);
//             exit(-1);
//         }
//         else
//         {
//             ft_printf("%d %s \n", i, game->map.map[i]);
// ///PLEASE MALLOC
//             game->map.rows++;
//             check_line(game, game->map.map[i]);
//         }
//         i++;
//     }
// 	ft_printf("Map checked");
// }


void	read_map(int fd, t_game *game)
{
    int i;
	char *line;

    i = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(line == NULL)
			break;
        if(line[ft_strlen(line)-1] == '\n')
			line[ft_strlen(line)-1] = '\0';
        if (i == 0)
            game->map.cols = ft_strlen(line);
		check_line(game, line);
        free(line);
		i++;
	}
	close(fd);
    save_map(fd, game);
}

void save_map(int fd, t_game *game)
{
    game->map.map = malloc(game->map.rows * sizeof(char *));
}
