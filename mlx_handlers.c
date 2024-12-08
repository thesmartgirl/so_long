/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by ataan             #+#    #+#             */
/*   Updated: 2024/12/08 18:59:01 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	if(game->border.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->border.img_ptr);
	if(game->wall.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->wall.img_ptr);
	if(game->player.image.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->player.image.img_ptr);
	if(game->bckgrnd.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->bckgrnd.img_ptr);
	if(game->exit.image.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->exit.image.img_ptr);
	if(game->collect.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->collect.img_ptr);
	if(game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
}

int	close_x(t_game *game)
{
	char *msg;

	msg = "";
	close_window(game, msg);
	return (0);
}

int	close_window(t_game *game, char *msg)
{
	free_map(game->map);
	if (game->images_init == 1)
	{
		destroy_images(game);
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
	}
	ft_printf("%s", msg);
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
	return (0);
}

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

void	win_game(t_game *game)
{
	close_window(game, "You WON the game :)\n");
}
