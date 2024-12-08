/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:08 by ataan             #+#    #+#             */
/*   Updated: 2024/12/08 19:27:49 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map_error(int err)
{
	
	if(err == 1)
		ft_printf("Can not open map\n");
	else if(err == 2)
		ft_printf("Map not rectangular\n");
	else if(err == 3)
		ft_printf("Map contains invalid characters\n");
	exit(-1);
}

void	free_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.rows)
	{
		free(map.map[i]);
		i++;	
	}
	free(map.map);
}

void	check_line(t_game *game, char *line, int line_no)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(line))
	{
		if ((int)ft_strlen(line) != game->map.cols)
		{
			ft_printf("%d\n", game->map.rows);
			read_map_error(2);}
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
		{
			ft_printf("%d\n", game->map.rows);
			read_map_error(3);
			free_map(game->map);
		}
		j++;
	}
}

void	read_map(char *file, t_game *game)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		read_map_error(1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (i == 0)
			game->map.cols = ft_strlen(line);
		check_line(game, line, i);
		game->map.rows++;
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
		read_map_error(1);
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
