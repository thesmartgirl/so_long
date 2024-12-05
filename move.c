/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:44 by ataan             #+#    #+#             */
/*   Updated: 2024/12/05 17:46:46 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect(t_game *game, int new_i, int new_j)
{
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->bckgrnd.img_ptr, (32 * game->player.j), (game->player.i * 32));
	game->map.map[game->player.i][game->player.j] = '0';
	game->player.i = new_i;
	game->player.j = new_j;
	game->map.map[game->player.i][game->player.j] = 'P';
	game->player.collected++;
	game->player.moves++;
	ft_printf("collectibles = %d\n", game->player.collected);
	ft_printf("moves = %d\n", game->player.moves);
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->player.image.img_ptr, (32 * game->player.j), (game->player.i
			* 32));
	if (game->player.collected == game->map.collectibles)
		render_exit(game);
}

void	free_move(t_game *game, int new_i, int new_j)
{
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->bckgrnd.img_ptr, (32 * game->player.j), (game->player.i * 32));
	game->map.map[game->player.i][game->player.j] = '0';
	game->player.i = new_i;
	game->player.j = new_j;
	game->map.map[game->player.i][game->player.j] = 'P';
	game->player.moves++;
	ft_printf("moves = %d\n", game->player.moves);
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->player.image.img_ptr, (32 * game->player.j), (game->player.i
			* 32));
}

void	move_vertical(t_game *game, int d)
{
	int	new_row;

	// ft_printf("move_vertical %d %d %d\n", game->player.i, game->player.j, d);
	new_row = game->player.i + d;
	if (game->map.map[new_row][game->player.j] == '0')
		free_move(game, new_row, game->player.j);
	else if (game->map.map[new_row][game->player.j] == 'C')
		collect(game, new_row, game->player.j);
	else if (game->map.map[new_row][game->player.j] == 'E')
	{
		// ft_printf("exiting %d %d\n", game->player.collected,
		//	game->map.collectibles);
		if (game->player.collected == game->map.collectibles)
			win_game(game);
		else
			free_move(game, new_row, game->player.j);
	}
}

void	move_horizontal(t_game *game, int d)
{
	int	new_col;

	// ft_printf("move_horizontal %d %d %d\n", game->player.i, game->player.j,
	//	d);
	new_col = game->player.j + d;
	// ft_printf("move_horizontal - 2 %c %d %d\n",
	//	game->map.map[game->player.i][new_col], game->player.i, new_col);
	if (game->map.map[game->player.i][new_col] == '0')
		free_move(game, game->player.i, new_col);
	else if (game->map.map[game->player.i][new_col] == 'C')
		collect(game, game->player.i, new_col);
	else if (game->map.map[game->player.i][new_col] == 'E')
	{
		ft_printf("exiting %d %d\n", game->player.collected,
			game->map.collectibles);
		if (game->player.collected == game->map.collectibles)
			win_game(game);
		else
			free_move(game, game->player.i, new_col);
	}
}
