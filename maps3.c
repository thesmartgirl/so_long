/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:39 by ataan             #+#    #+#             */
/*   Updated: 2024/12/09 17:43:14 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(t_map map, int err)
{
	if (err == 1)
		ft_printf("Can not open map\n");
	else if (err == 2)
		ft_printf("Map not rectangular\n");
	else if (err == 3)
		ft_printf("Map contains invalid characters\n");
	else if (err == 4)
		ft_printf("Wrong number of exits in map\n");
	else if (err == 5)
		ft_printf("Wrong number of players in map\n");
	else if (err == 6)
		ft_printf("No collectibles in map\n");
	else if (err == 7)
		ft_printf("Exit and/or some collectibles not reachable \n");
	else if (err == 8)
		ft_printf("Map border error\n");
	else if (err == 9)
		ft_printf("Malloc failure while copying map\n");
	else
		ft_printf("Unknown map error\n");
	map_free(map);
	exit(-1);
}

void	map_free(t_map map)
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

t_map	map_copy(t_game *game)
{
	t_map	tmp_map;
	int		i;

	tmp_map.map = malloc(game->map.rows * sizeof(char *));
	if (!tmp_map.map)
		map_error(game->map, 9);
	i = 0;
	while (i < game->map.rows)
	{
		tmp_map.map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	tmp_map.rows = game->map.rows;
	tmp_map.cols = game->map.cols;
	return (tmp_map);
}
