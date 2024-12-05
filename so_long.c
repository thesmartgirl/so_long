/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:39 by ataan             #+#    #+#             */
/*   Updated: 2024/12/05 18:18:17 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
}

void	read_map(t_game *game)
{
	game->map.rows = 7;
	game->map.cols = 16;
	game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
	game->map.map = malloc((game->map.rows + 1) * sizeof(char *));
	game->map.map[0] = ft_strdup("1111111111111111");
	game->map.map[1] = ft_strdup("1010010000100001");
	game->map.map[2] = ft_strdup("1000C010C0010101");
	game->map.map[3] = ft_strdup("1C0000E000010101");
	game->map.map[4] = ft_strdup("10001000P0010101");
	game->map.map[5] = ft_strdup("1000001000010101");
	game->map.map[6] = ft_strdup("1111111111111111");
	game->map.map[7] = NULL;
}

void	init_player(t_game *game)
{
	game->player.collected = 0;
	game->player.moves = 0;
}

void	init_images(t_game *game)
{
	game->border.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/border.xpm", &game->border.img_h, &game->border.img_w);
	if (game->border.img_ptr == NULL)
	{
		ft_printf("Couldn't find border.xpm. Does it exist?");
		exit(-1);
	}
	game->bckgrnd.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/grass.xpm", &game->bckgrnd.img_h, &game->bckgrnd.img_w);
	if (game->bckgrnd.img_ptr == NULL)
		ft_printf("Couldn't find grass.xpm. Does it exist?");
	game->wall.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/wall.xpm", &game->wall.img_h, &game->wall.img_w);
	if (game->wall.img_ptr == NULL)
		ft_printf("Couldn't find wall.xpm. Does it exist?");
	game->player.image.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/ducky.xpm", &game->player.image.img_h,
			&game->player.image.img_w);
	if (game->player.image.img_ptr == NULL)
		ft_printf("Couldn't find ducky.xpm. Does it exist?");
	game->exit.image.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/exit.xpm", &game->exit.image.img_h,
			&game->exit.image.img_w);
	if (game->exit.image.img_ptr == NULL)
		ft_printf("Couldn't find exit.xpm. Does it exist?");
	game->collect.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx,
			"./textures/collect.xpm", &game->collect.img_h,
			&game->collect.img_w);
	if (game->collect.img_ptr == NULL)
		ft_printf("Couldn't find collect.xpm. Does it exist?");
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		map_fd;

	//  check_args(argc, argv);
	read_map(&game);
	initialize_mlx(&game);
	check_map(&game);
	init_player(&game);
	render_map(&game);
	mlx_key_hook(game.mlx_data.win, key_inputs, &game);
	mlx_hook(game.mlx_data.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx_data.mlx);
	return (0);
}
