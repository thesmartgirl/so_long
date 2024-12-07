#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx.h>

typedef enum e_error_code
{
	no_error = 0,
	general_error = -1,
	arg_err = -2,
	map_error = -3,
}				t_error_code;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			cols;
	int			exits;
	int			players;
	int			collectibles;

}				t_map;

typedef struct s_image
{
	void		*img_ptr;
	int			img_h;
	int			img_w;

}				t_image;

typedef struct s_mlxdata
{
	void		*mlx;
	void		*win;
}				t_mlx_data;

typedef struct s_player
{
	t_image		image;
	int			i;
	int			j;
	int			collected;
	int			moves;
}				t_player;

typedef struct s_exit
{
	t_image		image;
	int			i;
	int			j;
}				t_exit;

typedef struct s_game
{
	t_mlx_data	mlx_data;
	t_map		map;
	t_image		tile;
	t_image		border;
	t_image		wall;
	t_player	player;
	t_image		collect;
	t_exit		exit;
	t_image		enemy;
	t_image		bckgrnd;
}				t_game;

void			destroy_images(t_game *game);
void			free_map(t_game *game);
int				close_window(t_game *game);
void			render_exit(t_game *game);
void			win_game(t_game *game);
void			collect(t_game *game, int new_i, int new_j);
void			free_move(t_game *game, int new_i, int new_j);
void			move_vertical(t_game *game, int d);
void			move_horizontal(t_game *game, int d);
int				key_inputs(int keysym, t_game *game);
void			check_args(int argc, char **argv);
void			init_player(t_game *game);
void			init_images(t_game *game);
void			tile_to_print(t_game *game, int i, int j);
void			render_map(t_game *game);
int				initialize_mlx(t_game *game);
void			check_borders(t_game *game);
void			check_counts(t_game *game);
void			check_map(t_game *game);
void			free_map(t_game *game);
void			check_line(t_game *game, char *line, int line_no);
void			init_map(t_game *game);
void			read_map(char *file, t_game *game);
void			save_map(char *file, t_game *game);

#endif
