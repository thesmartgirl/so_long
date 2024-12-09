/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by ataan             #+#    #+#             */
/*   Updated: 2024/12/09 17:41:07 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	if (game->border.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->border.img_ptr);
	if (game->wall.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->wall.img_ptr);
	if (game->player.image.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->player.image.img_ptr);
	if (game->bckgrnd.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->bckgrnd.img_ptr);
	if (game->exit.image.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->exit.image.img_ptr);
	if (game->collect.img_ptr)
		mlx_destroy_image(game->mlx_data.mlx, game->collect.img_ptr);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
}

int	close_x(t_game *game)
{
	char	*msg;

	msg = "Normal Exit\n";
	close_window(game, msg);
	return (0);
}

int	close_window(t_game *game, char *msg)
{
	map_free(game->map);
	if (game->images_init == 1)
	{
		destroy_images(game);
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
	}
	ft_printf("%s", msg);
	exit(0);
}

void	win_game(t_game *game)
{
	close_window(game, "You WON the game :)\n");
}
