#include "so_long.h"
#include <X11/keysym.h>
#include <mlx.h>
#include "../libft/libft.h"
#include <fcntl.h>


int     key_inputs(int keysym, t_mlx_data *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    return (0);
}

void    close_window(t_mlx_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(1);
}

int     check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Wrong Number of Arguments :(\n)");
        return 0;
    }
    if (ft_strncmp(".ber",ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4),4))
    {
        ft_printf("Invalid File Type :(\n)");
        return 0;
    }
    if (open(argv[1], O_RDONLY) == -1)
    {
        ft_printf("Map File not found :(\n)");
        return 0;
    }
}
    

    

int     main(int argc, char **argv)
{
    t_mlx_data mlx_data;
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
    mlx_hook(mlx_data.win, 17, 0, close_window, &mlx_data);
    mlx_loop(mlx_data.mlx);
    return (0);
}