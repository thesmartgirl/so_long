/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:44 by ataan             #+#    #+#             */
/*   Updated: 2024/12/10 20:19:22 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	called by the mlx hook, 
	decides what to do based on keysym
*/
int	key_inputs(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_window(game, "Normal Exit\n");
	else if (keysym == XK_Up)
		move_vertical(game, -1);
	else if (keysym == XK_Down)
		move_vertical(game, 1);
	else if (keysym == XK_Right)
		move_horizontal(game, 1);
	else if (keysym == XK_Left)
		move_horizontal(game, -1);
	return (0);
}

/*
	moves the player up/down,
	depending on map character and counters, calls one of the functions:
		free_move
		collect
		win_game
*/
void	move_vertical(t_game *game, int d)
{
	int	new_row;

	new_row = game->player.i + d;
	if (game->map.map[new_row][game->player.j] == '0')
		free_move(game, new_row, game->player.j);
	else if (game->map.map[new_row][game->player.j] == 'C')
		collect(game, new_row, game->player.j);
	else if (game->map.map[new_row][game->player.j] == 'E')
	{
		if (game->player.collected == game->map.collectibles)
			win_game(game);
		else
			free_move(game, new_row, game->player.j);
	}
}

/*
	moves the player right/left,
	depending on map character and counters, calls one of the functions:
		free_move
		collect
		win_game
*/
void	move_horizontal(t_game *game, int d)
{
	int	new_col;

	new_col = game->player.j + d;
	if (game->map.map[game->player.i][new_col] == '0')
		free_move(game, game->player.i, new_col);
	else if (game->map.map[game->player.i][new_col] == 'C')
		collect(game, game->player.i, new_col);
	else if (game->map.map[game->player.i][new_col] == 'E')
	{
		if (game->player.collected == game->map.collectibles)
			win_game(game);
		else
			free_move(game, game->player.i, new_col);
	}
}

/*
	used when a collectible is found.
	renders previous position,
	updates player position,
	updates and displays collectibles and moves counters,
	renders new player position,
	render exit if needed
*/
void	collect(t_game *game, int new_i, int new_j)
{
	free_move(game, new_i, new_j);
	game->player.collected++;
	ft_printf("collectibles = %d\n", game->player.collected);
	if (game->player.collected == game->map.collectibles)
		render_exit(game);
}

/*
	for valid, normal moves.  
	renders previous position,
	updates player position,
	updates and displays moves counter,
	renders new player position
*/
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
