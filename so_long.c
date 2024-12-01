#include "../includes/so_long.h"
#include <X11/keysym.h>
#include <mlx.h>
#include "../libft/libft.h"
#include <fcntl.h>

int    close_window(t_game *game)
{
    mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
    mlx_destroy_display(game->mlx_data.mlx);
    free(game->mlx_data.mlx);
    exit(1);
}

int     key_inputs(int keysym, t_game *game)
{
    if (keysym == XK_Escape)
        close_window(game);
    return (0);
}

int     check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Wrong Number of Arguments :(\n");
        return 0;
    }
    if (ft_strncmp(".ber",ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4),4))
    {
        ft_printf("Invalid File Type :(\n");
        return 0;
    }
    if (open(argv[1], O_RDONLY) == -1)
    {
        ft_printf("Map File not found :(\n");
        return 0;
    }
    return 1;
}

void read_map(t_game game)
{
    game.player.img_h = 1;
}

int     main(int argc, char **argv)
{
    t_mlxdata mlx_data;
    t_game  game;
    int map_fd;

    if(!check_args(argc, argv))
        return -1;
    read_map(game);
	mlx_data.mlx = mlx_init();  
	if (!mlx_data.mlx)
		return (-1);
	mlx_data.win = mlx_new_window(mlx_data.mlx,
								700,
								700,
								"Ducky Walk");
	if (!mlx_data.win)
    {
        mlx_destroy_display(mlx_data.mlx);
        free(mlx_data.mlx);
        return (-1);
    }
    mlx_key_hook(mlx_data.win, key_inputs, &mlx_data);
    mlx_hook(game.mlx_data.win, 17, 0, close_window, &game);
    mlx_loop(mlx_data.mlx);
    return (0);
}