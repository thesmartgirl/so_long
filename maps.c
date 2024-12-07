/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:08 by ataan             #+#    #+#             */
/*   Updated: 2024/12/07 19:21:34 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	check_line(t_game *game, char *line, int line_no)
{
	int	j;

	j = 0;
	while (j < ft_strlen(line))
	{
		if (ft_strlen(line) != game->map.cols)
			exit(-1);
		if (line[j] == 'P')
		{
			game->map.players++;
			game->player.i = line_no;
			game->player.j = j;
		}
		else if (line[j] == 'E')
		{
			game->map.exits++;
			game->exit.i = line_no;
			game->exit.j = j;
		}
		else if (line[j] == 'C')
			game->map.collectibles++;
		else if (line[j] != '0' && line[j] != '1')
			exit(-1);
		j++;
	}
}

void	init_map(t_game *game)
{
	game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
	game->map.rows = 0;
	game->map.cols = 0;
}

void	read_map(char *file, t_game *game)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		game->map.rows++;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (i == 0)
			game->map.cols = ft_strlen(line);
		check_line(game, line, i);
		free(line);
		i++;
	}
	close(fd);
	save_map(file, game);
}

void	save_map(char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(-1);
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
