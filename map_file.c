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
