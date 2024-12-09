/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:47:21 by ataan             #+#    #+#             */
/*   Updated: 2024/12/09 17:43:14 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_border_check(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map.cols)
	{
		if (game->map.map[0][j] != '1' || game->map.map[game->map.rows
			- 1][j++] != '1')
			map_error(game->map, 8);
	}
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i][0] != '1' || game->map.map[i][game->map.cols
			- 1] != '1')
			map_error(game->map, 8);
		i++;
	}
}

int	map_dfs_check(t_game *game, t_map map, int i, int j)
{
	static int	exits;
	static int	collects;

	if (map.map[i][j] == 'F' || i == map.rows || j == map.cols || i == 0
		|| j == 0 || map.map[i][j] == '1')
		return (0);
	if (map.map[i][j] == 'E')
		exits += 1;
	if (map.map[i][j] == 'C')
		collects += 1;
	map.map[i][j] = 'F';
	map_dfs_check(game, map, i - 1, j);
	map_dfs_check(game, map, i, j + 1);
	map_dfs_check(game, map, i + 1, j);
	map_dfs_check(game, map, i, j - 1);
	if (exits != 1)
		return (-1);
	if (collects != game->map.collectibles)
		return (-1);
	return (0);
}

int	map_valid_path_check(t_game *game, t_map tmp_map)
{
	return (map_dfs_check(game, tmp_map, game->player.i, game->player.j));
}

void	map_check(t_game *game)
{
	t_map	tmp_map;
	int		valid_path;

	map_pre_check(game);
	map_border_check(game);
	if (game->map.exits != 1)
		map_error(game->map, 4);
	else if (game->map.players != 1)
		map_error(game->map, 5);
	else if (game->map.collectibles < 1)
		map_error(game->map, 6);
	else
	{
		tmp_map = map_copy(game);
		valid_path = map_valid_path_check(game, tmp_map);
		map_free(tmp_map);
		if (valid_path == -1)
			map_error(game->map, 7);
	}
}
