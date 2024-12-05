#include "so_long.h"
#include <X11/keysym.h>
#include <mlx.h>
#include "../libft/libft.h"
#include <fcntl.h>



void    render_exit(t_game *game)
{
        mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
                          game->exit.image.img_ptr, (32 * game->exit.j),
                          (game->exit.i * 32));
}

void    win_game(t_game *game)
{
  printf("You WON the game :)\n");
  close_window(game);
  exit(0);
}

void    collect(t_game *game, int new_i, int new_j)
{
      mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
                              game->bckgrnd.img_ptr, (32 * game->player.j),
                              (game->player.i * 32));
      game->map.map[game->player.i][game->player.j] = '0';
      game->player.i = new_i;
      game->player.j = new_j;
      game->map.map[game->player.i][game->player.j] = 'P';
      game->player.collected++;
      game->player.moves++;
      printf("collectibles = %d\n", game->player.collected);
      printf("moves = %d\n", game->player.moves);
      mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
                              game->player.image.img_ptr, (32 * game->player.j),
                              (game->player.i * 32));
      if(game->player.collected == game->map.collectibles)
        render_exit(game);
}

void    free_move(t_game *game, int new_i, int new_j)
{
      mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
                              game->bckgrnd.img_ptr, (32 * game->player.j),
                              (game->player.i * 32));
      game->map.map[game->player.i][game->player.j] = '0';
      game->player.i = new_i;
      game->player.j = new_j;
      game->map.map[game->player.i][game->player.j] = 'P';
      game->player.moves++;
      printf("moves = %d\n", game->player.moves);
      mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
                              game->player.image.img_ptr, (32 * game->player.j),
                              (game->player.i * 32));
}

void    move_vertical(t_game *game, int d)
{
        int     new_row;

        new_row = game->player.i + d;
        if (game->map.map[new_row][game->player.j] == '0')
            free_move(game, new_row, game->player.j);
         else if (game->map.map[new_row][game->player.j] == 'C')
            collect(game, new_row, game->player.j);
         else if (game->map.map[new_row][game->player.j] == 'E' )
         {
           if(game->player.collected == game->map.collectibles)
                win_game(game);
           else
                free_move(game, new_row, game->player.j);
         }
}

void    move_horizontal(t_game *game, int d)
{
        int     new_col;

        new_col= game->player.j + d;
        if (game->map.map[game->player.i][new_col] == '0')
             free_move(game, game->player.i, new_col);
        else if (game->map.map[game->player.i][new_col] == 'C')
             collect(game, game->player.i, new_col);
        else if (game->map.map[game->player.i][new_col] == 'E' )
        {
           if(game->player.collected == game->map.collectibles)
                win_game(game);
           else
                free_move(game, game->player.i, new_col);
        }
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

void     check_args(int argc, char **argv)
{
    char *tmp;

    if (argc != 2)
    {
        ft_printf("Wrong Number of Arguments :(\n");
        exit(-1);
    }
    tmp = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
    if (ft_strncmp(".ber", tmp,4))
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
    exit(-1);
}

void    read_map(t_game *game)
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
    game->map.map[3] = ft_strdup("1C00000000010101");
    game->map.map[4] = ft_strdup("10001000P0010101");
    game->map.map[5] = ft_strdup("10E0001000010101");
    game->map.map[6] = ft_strdup("1111111111111111");
    game->map.map[7] = NULL;
}

void    init_player(t_game *game)
{
  game->player.collected = 0;
  game->player.moves = 0;
}

void    init_images(t_game *game)
{
    game->border.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/border.xpm", &game->border.img_h, &game->border.img_w);
    if (game->border.img_ptr== NULL)
		ft_printf("Couldn't find border.xpm. Does it exist?");
    game->bckgrnd.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/grass.xpm", &game->bckgrnd.img_h, &game->bckgrnd.img_w);
    if (game->bckgrnd.img_ptr== NULL)
		ft_printf("Couldn't find grass.xpm. Does it exist?");
    game->wall.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/wall.xpm", &game->wall.img_h, &game->wall.img_w);
    if (game->wall.img_ptr== NULL)
		ft_printf("Couldn't find wall.xpm. Does it exist?");
    game->player.image.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/ducky.xpm", &game->player.image.img_h, &game->player.image.img_w);
    if (game->player.image.img_ptr== NULL)
		ft_printf("Couldn't find ducky.xpm. Does it exist?");
    game->exit.image.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/exit.xpm", &game->exit.image.img_h, &game->exit.image.img_w);
    if (game->exit.image.img_ptr== NULL)
		ft_printf("Couldn't find exit.xpm. Does it exist?");
    game->collect.img_ptr = mlx_xpm_file_to_image(game->mlx_data.mlx, "./textures/collect.xpm", &game->collect.img_h, &game->collect.img_w);
    if (game->collect.img_ptr== NULL)
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
        game->tile.img_ptr = game->player.image.img_ptr;
    else if (game->map.map[i][j] == 'E')
    {
        if (game->player.collected == game->map.collectibles)
          game->tile.img_ptr = game->exit.image.img_ptr;
        else
           game->tile.img_ptr = game->bckgrnd.img_ptr;
    }
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
            exit(-1);
}

void    check_counts(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while(j < game->map.cols)
        {
            if(game->map.map[i][j] == 'P')
            {
                game->map.players++;
                game->player.i = i;
                game->player.j = j;
            }
            else if(game->map.map[i][j] == 'C')
                game->map.collectibles++;
            else if(game->map.map[i][j] == 'E')
            {
                game->map.exits++;
                game->exit.i = i;
                game->exit.j = j;
            }
            else if(game->map.map[i][j] != '1' && game->map.map[i][j] != '0')
              exit(-1);
            j++;
        }
        i++;
    }
    if (game->map.players != 1 || game->map.exits != 1 || game->map.collectibles < 1)
        exit(-1);
}

void     check_map(t_game *game)
{
    check_borders(game);
    check_counts(game);
            //check_nulls()???
            //check_rectangle;??
            // check_valid_path();
}

int     main(int argc, char **argv)
{
    t_game  game;
    int map_fd;

    check_args(argc, argv);
    initialize_mlx(&game);
    read_map(&game);
    check_map(&game);
    render_map(&game);
    init_player(&game);
    mlx_key_hook(game.mlx_data.win, key_inputs, &game);
    mlx_hook(game.mlx_data.win, 17, 0, close_window, &game);
    mlx_loop(game.mlx_data.mlx);
    return (0);
}
