/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:47:11 by ataan             #+#    #+#             */
/*   Updated: 2024/12/05 17:47:12 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_exit(t_game *game)
{
	game->map.map[game->exit.i][game->exit.j] = 'E';
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->exit.image.img_ptr, (32 * game->exit.j), (game->exit.i * 32));
}

void	render_map(t_game *game)
{
	int	i;
	int	j;

	init_images(game);
	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.cols)
		{
			tile_to_print(game, i, j);
			mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
				game->tile.img_ptr, (32 * j), (i * 32));
			j++;
		}
		i++;
	}
}

void	tile_to_print(t_game *game, int i, int j)
{
	// ft_printf("tile_to_print %d %d %d %d\n", i, j, game->map.rows,game-> map.cols);
	if (i == 0 || i == game->map.rows - 1 || j == 0 || j == game->map.cols - 1)
		game->tile.img_ptr = game->border.img_ptr;
	else if (game->map.map[i][j] == '1')
		game->tile.img_ptr = game->wall.img_ptr;
	else if (game->map.map[i][j] == '0')
		game->tile.img_ptr = game->bckgrnd.img_ptr;
	else if (game->map.map[i][j] == 'P')
		game->tile.img_ptr = game->player.image.img_ptr;
	else if (game->map.map[i][j] == 'E')
	{
		if (game->player.collected == game->map.collectibles)
			game->tile.img_ptr = game->exit.image.img_ptr;
		else
			game->tile.img_ptr = game->bckgrnd.img_ptr;
	}
	else if (game->map.map[i][j] == 'C')
		game->tile.img_ptr = game->collect.img_ptr;
}
