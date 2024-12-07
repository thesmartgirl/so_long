/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:47:21 by ataan             #+#    #+#             */
/*   Updated: 2024/12/07 20:15:17 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_args(int argc, char **argv)
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

void	check_borders(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map.cols)
	{
		if (game->map.map[0][j] != '1' || game->map.map[game->map.rows
			- 1][j++] != '1')
			exit(-1);
	}
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i][0] != '1' || game->map.map[i][game->map.cols
			- 1] != '1')
			exit(-1);
		i++;
	}
}

void dfs( char **map, int i, int j, int *exits, int *coins)
{
    if (map[i][j] == 'F' || i == game->map.rows || j == game->map.cols || i == 0 || j == 0 || map[i][j] == '1')
        return;
    if(map[i][j] == 'E')
        *(exits) += 1;
    if(map[i][j] == 'C')
        *(coins) += 1;
    map[i][j] = 'F';
    dfs(map, i - 1, j, exits, coins);
    dfs(map, i, j + 1, exits, coins);
    dfs(map, i + 1, j, exits, coins);
    dfs(map, i, j - 1, exits, coins);
}

void check_valid_path(char **map, int i, int j, char newClr)
{
	    int prevClr;
	    int exits;
	    int coins;

			exits=0;
	    coins=0;
	    dfs(map, i, j, &exits, &coins);
	    printf("exits %d, coins %d\n", exits, coins);
	}
}

void	check_map(t_game *game)
{
	check_borders(game);
	// check_nulls()???
	check_valid_path(game->map.map,
								game->player.i,
								game->player.j,
								'F');
}
