/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:06 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/12 22:44:58 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define MAX_WIDTH		60
# define MAX_HEIGHT		30

# define KEY_W			1731
# define KEY_A			1734
# define KEY_S			1753
# define KEY_D			1751
# define KEY_ESC		65307

# define BACK			0
# define WALL			1
# define DOOR			2
# define ITEM			3

# define CHAR_BACK		4
# define CHAR_LEFT		5
# define CHAR_FRONT		6
# define CHAR_RIGHT		7

# define CHAR_DOOR		8
# define CHAR_ITEM		9

# define DOOR_OPEN		10	
# define EXIT			11

# define ASSETS			12

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

typedef struct s_data
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int	data[4096];
	int	w;
	int	h;
	int	exit_x;
	int	exit_y;
	int	x;
	int	y;
	int	points;
	int	points_to_finish;
	int	steps;
}				t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	assets[ASSETS];
	t_map	*map;
}				t_game;

int	render_pos(t_game *game, int asset, int x, int y);
int	render(t_game *game, int asset, int *dir, int dir_enum);
int	render_map(t_game *game);

int	load_assets(t_game *game);
int	load_map(t_map *map, char *map_name);

#endif
