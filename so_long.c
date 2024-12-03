#include "../includes/so_long.h"
#include <X11/keysym.h>
#include <mlx.h>
#include "../libft/libft.h"
#include <fcntl.h>

void destroy_images(t_game *game)
{
    mlx_destroy_image(game->mlx_data.mlx, game->border.img_ptr);
    mlx_destroy_image(game->mlx_data.mlx, game->wall.img_ptr);
    mlx_destroy_image(game->mlx_data.mlx, game->player.img_ptr);
    mlx_destroy_image(game->mlx_data.mlx, game->bckgrnd.img_ptr);
    mlx_destroy_image(game->mlx_data.mlx, game->exit.img_ptr);
    mlx_destroy_image(game->mlx_data.mlx, game->collect.img_ptr);
    mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
}
void    free_map(t_game *game)
{
    int i = 0;
    while (i < game->map.rows)
    {
        free(game->map.map[i]);
        i++;
    }
    free(game->map.map);
}

int    close_window(t_game *game)
{
    free_map(game);
    destroy_images(game);
    mlx_destroy_display(game->mlx_data.mlx);
    free(game->mlx_data.mlx);
    exit(0);
}

int     key_inputs(int keysym, t_game *game)
{
    if (keysym == XK_Escape)
        close_window(game);
    return (0);
}

int     check_args(int argc, char **argv)
{
    char *tmp;

    if (argc != 2)
    {
        ft_printf("Wrong Number of Arguments :(\n");
        return 0;
    }
    tmp = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
    if (ft_strncmp(".ber", tmp,4))
    {
        ft_printf("Invalid File Type :(\n");
        free(tmp);
        return 0;
    }
    if (open(argv[1], O_RDONLY) == -1)
    {
        ft_printf("Map File not found :(\n");
        free(tmp);
        return 0;
    }
    free(tmp);
    return 1;
}

void    read_map(t_game *game)
{
    game->map.rows = 7;
    game->map.cols = 16;
    game->map.map = malloc((game->map.rows + 1) * sizeof(char *));
    game->map.map[0] = ft_strdup("1111111111111111");
    game->map.map[1] = ft_strdup("1010010000100001");
    game->map.map[2] = ft_strdup("1000C010C0010101");
    game->map.map[3] = ft_strdup("1C00000000010101");
    game->map.map[4] = ft_strdup("10001000P0010101");
    game->map.map[5] = ft_strdup("10E0001000010101");
    game->map.map[6] = ft_strdup("1111111111111111");
    game->map.map[7] = NULL;
}

void    init_images(t_game *game)
{
    game->border.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/border.xpm", &game->border.img_h, &game->border.img_w);
    if (game->border.img_ptr== NULL)
		ft_printf("Couldn't find border.xpm. Does it exist?");
    game->bckgrnd.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/grass.xpm", &game->bckgrnd.img_h, &game->bckgrnd.img_w);
    if (game->bckgrnd.img_ptr== NULL)
		ft_printf("Couldn't find grass.xpm. Does it exist?");
    game->wall.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/wall.xpm", &game->wall.img_h, &game->wall.img_w);
    if (game->wall.img_ptr== NULL)
		ft_printf("Couldn't find wall.xpm. Does it exist?");
    game->player.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/ducky.xpm", &game->player.img_h, &game->player.img_w);
    if (game->player.img_ptr== NULL)
		ft_printf("Couldn't find ducky.xpm. Does it exist?");
    game->exit.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/exit.xpm", &game->exit.img_h, &game->exit.img_w);
    if (game->exit.img_ptr== NULL)
		ft_printf("Couldn't find exit.xpm. Does it exist?");
    game->collect.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "../assets/collect.xpm", &game->collect.img_h, &game->collect.img_w);
    if (game->exit.img_ptr== NULL)
		ft_printf("Couldn't find collect.xpm. Does it exist?");
}

void    tile_to_print(t_game *game, int i, int j)
{
    if(i == 0 || i == game->map.rows - 1 || j == 0 || j == game->map.cols - 1)
        game->tile.img_ptr = game->border.img_ptr;
    else if (game->map.map[i][j] == '1')
        game->tile.img_ptr = game->wall.img_ptr;
    else if (game->map.map[i][j] == '0')
        game->tile.img_ptr = game->bckgrnd.img_ptr;
    else if (game->map.map[i][j] == 'P')
        game->tile.img_ptr = game->player.img_ptr;
    else if (game->map.map[i][j] == 'E')
        game->tile.img_ptr = game->exit.img_ptr;
    else if (game->map.map[i][j] == 'C')
        game->tile.img_ptr = game->collect.img_ptr; 
}

void    render_map(t_game *game)
{
    int i;
    int j;

    init_images(game);
    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while(j < game->map.cols)
        {
            tile_to_print(game, i, j);
            mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win, game->tile.img_ptr, (32 * j), (i * 32));
            j++;
        }
        i++;
    }
}

int     initialize_mlx(t_game *game)
{
    game->mlx_data.mlx = mlx_init();  
	if (!game->mlx_data.mlx)
		return (-1);
	game->mlx_data.win = mlx_new_window(game->mlx_data.mlx,
								game->map.cols * 32,
								game->map.rows * 32,
								"Ducky Walk");
	if (!game->mlx_data.win)
    {
        mlx_destroy_display(game->mlx_data.mlx);
        free(game->mlx_data.mlx);
        return (-1);
    }
}

void    check_borders(t_game *game)
{
    int i;
    int j;

    j = 0;
    while(j < game->map.cols)
        if(game->map.map[0][j] != '1' || game->map.map[game->map.rows - 1][j++] != '1')
            exit(-1);
    i = 0;
    while (i < game->map.rows)
        if(game->map.map[i][0] != '1' || game->map.map[i++][game->map.cols - 1] != '1' )
            exit(1);
}

void    check_counts(t_game *game)
{
    int i;
    int j;
    
    game->map.players = 0;
    game->map.exits = 0;
    game->map.collectibles = 0;
    i = 0;
        ft_printf("%d %d \n",game->map.rows, game->map.cols );
    while (i < game->map.rows)
    {
        j = 0;
        while(j < game->map.cols)
        {
            ft_printf("%d %d\n", i, j);
            if(game->map.map[i][j] == 'P')
                game->map.players++;
            if(game->map.map[i][j] == 'C')
                game->map.collectibles++;
            if(game->map.map[i][j] == 'E')
                game->map.exits++;
            j++;
        }
        i++;
    }
    ft_printf("%d %d %d\n", game->map.players, game->map.exits, game->map.collectibles);
    if (game->map.players != 1 || game->map.exits != 1 || game->map.collectibles < 1)
        exit(-1);
}

int check_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while(j < game->map.cols)
        {
            check_borders(game);
            check_counts(game);
            //check_nulls()???
            // check_exit();
            // check_collectible();
            // check_valid_path();
            j++;
        }
        i++;
    }
}

int     main(int argc, char **argv)
{
    t_game  game;
    int map_fd;

    // if(!check_args(argc, argv))
    //     return -1;
    read_map(&game);
    check_map(&game);
	if (initialize_mlx(&game) == -1)
        return (-1);
    render_map(&game);
    mlx_key_hook(game.mlx_data.win, key_inputs, &game);
    mlx_hook(game.mlx_data.win, 17, 0, close_window, &game);
    mlx_loop(game.mlx_data.mlx);
    return (0);
}