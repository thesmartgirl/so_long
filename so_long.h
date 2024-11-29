#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_game
{
    t_map   map;
    t_image border;
    t_image wall;
    t_image player;
    t_image collect;
    t_image enemy;
    t_image bckgrnd;
    

} t_game;

typedef struct s_map
{
    char    *map;
    int     rows;
    int     cols;
} t_map;

typedef struct s_image
{
    void    *img_ptr;
    int     img_h;
    int     img_w;

} t_image;

typedef struct s_mlx_data
{
    void	*mlx;
    void	*win;
}               t_mlx_data;

#endif