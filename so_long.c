/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:39 by ataan             #+#    #+#             */
/*   Updated: 2024/12/10 19:24:31 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_args(int argc, char **argv)
{
	char	*tmp;

	if (argc != 2)
	{
		ft_printf("Wrong Number of Arguments :(\n");
		exit(-1);
	}
	tmp = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strncmp(".ber", tmp, 4))
	{
		ft_printf("Invalid File Type :(\n");
		free(tmp);
		exit(-1);
	}
	if (open(argv[1], O_RDONLY) == -1)
	{
		ft_printf("Map File not found :(\n");
		free(tmp);
		exit(-1);
	}
	free(tmp);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	init_map(&game);
	map_read(argv[1], &game);
	map_save(argv[1], &game);
	map_check(&game);
	init_mlx(&game);
	init_player(&game);
	render_map(&game);
	mlx_hook(game.mlx_data.win, 02, 03, key_inputs, &game);
	mlx_hook(game.mlx_data.win, 17, 0, close_x, &game);
	mlx_loop(game.mlx_data.mlx);
	return (0);
}
