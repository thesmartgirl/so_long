/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by ataan             #+#    #+#             */
/*   Updated: 2024/12/05 17:46:59 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_data.mlx, game->border.img_ptr);
	mlx_destroy_image(game->mlx_data.mlx, game->wall.img_ptr);
	mlx_destroy_image(game->mlx_data.mlx, game->player.image.img_ptr);
	mlx_destroy_image(game->mlx_data.mlx, game->bckgrnd.img_ptr);
	mlx_destroy_image(game->mlx_data.mlx, game->exit.image.img_ptr);
	mlx_destroy_image(game->mlx_data.mlx, game->collect.img_ptr);
	mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
}

int	close_window(t_game *game)
{
	free_map(game);
	destroy_images(game);
	mlx_destroy_display(game->mlx_data.mlx);
	free(game->mlx_data.mlx);
	exit(0);
}

int	initialize_mlx(t_game *game)
{
	game->mlx_data.mlx = mlx_init();
	if (!game->mlx_data.mlx)
		return (-1);
	game->mlx_data.win = mlx_new_window(game->mlx_data.mlx, game->map.cols * 32,
			game->map.rows * 32, "Ducky Walk");
	if (!game->mlx_data.win)
	{
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
		return (-1);
	}
}

int	key_inputs(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_window(game);
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

void	win_game(t_game *game)
{
	ft_printf("You WON the game :)\n");
	close_window(game);
	exit(0);
}
