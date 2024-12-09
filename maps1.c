/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:08 by ataan             #+#    #+#             */
/*   Updated: 2024/12/09 17:36:21 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_player(t_game *game, int i, int j)
{
	game->map.players++;
	game->player.i = i;
	game->player.j = j;
}

void	set_exit(t_game *game, int i, int j)
{
	game->map.exits++;
	game->exit.i = i;
	game->exit.j = j;
}

void	map_pre_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		if ((int)ft_strlen(game->map.map[i]) != game->map.cols)
			map_error(game->map, 2);
		j = 0;
		while (j < game->map.cols)
		{
			if (game->map.map[i][j] == 'P')
				set_player(game, i, j);
			else if (game->map.map[i][j] == 'E')
				set_exit(game, i, j);
			else if (game->map.map[i][j] == 'C')
				game->map.collectibles++;
			else if (game->map.map[i][j] != '0' && game->map.map[i][j] != '1')
				map_error(game->map, 3);
			j++;
		}
		i++;
	}
}

void	map_read(char *file, t_game *game)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		map_error(game->map, 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (i == 0)
			game->map.cols = (int)ft_strlen(line);
		game->map.rows++;
		free(line);
		i++;
	}
	close(fd);
}

void	map_save(char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		map_error(game->map, 1);
	game->map.map = (char **)malloc(game->map.rows * sizeof(char *));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map.map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
}
