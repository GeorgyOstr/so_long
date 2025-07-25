/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:06 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/20 17:25:13 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define RES			128

# define MAX_WIDTH		60
# define MAX_HEIGHT		30

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_FORWARD	65362	
# define KEY_LEFT		65361
# define KEY_BACK		65364
# define KEY_RIGHT		65363
# define KEY_ESC		65307

# define WALL				0
# define BACK				1
# define ITEM				2
# define DOOR				3

# define CHAR_BACK			4
# define CHAR_LEFT			5
# define CHAR_FRONT			6
# define CHAR_RIGHT			7

# define CHAR_DOOR			8
# define CHAR_ITEM			9

# define DOOR_OPEN			10
# define EXIT				11

# define CHAR_BACK_1		12
# define CHAR_LEFT_1		13
# define CHAR_FRONT_1		14
# define CHAR_RIGHT_1		15

# define STEP				8

# define ASSETS				16

# include "ft_printf.h"
# include "get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef struct s_data
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	int		data[4096];
	t_pos	dim;
	t_pos	exit;
	t_pos	p;
	int		points;
	int		points_to_finish;
	int		steps;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	assets[ASSETS];
	t_map	*map;
	t_pos	display;
}			t_game;

void		render_pos(t_game *game, int asset, int x, int y);
void		render(t_game *game, int asset, int *dir, int dir_enum);
void		render_map(t_game *game);

void		load_assets(t_game *game);
void		load_map(t_map *map, char *map_name);

void		error_file_extension(void);
void		error_file_exist(void);
void		error_map_check(void);
void		error_path_check(void);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);

int			check_extension(char *str);
int			checker(t_game *game);
#endif
