#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map
{
    char    **map;
    int     rows;
    int     cols;
    int     exits;
    int     players;
    int     collectibles;
    
} t_map;

typedef struct s_image
{
    void    *img_ptr;
    int     img_h;
    int     img_w;

} t_image;

typedef struct s_mlxdata
{
    void	*mlx;
    void	*win;
}               t_mlx_data;

typedef struct s_game
{
    t_mlx_data mlx_data;
    t_map   map;
    t_image tile;
    t_image border;
    t_image wall;
    t_image player;
    t_image collect;
    t_image exit;
    t_image enemy;
    t_image bckgrnd;
} t_game;


#endif