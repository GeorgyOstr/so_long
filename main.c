/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:09:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/10 23:52:09 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	render_pos(t_game *game, int asset, int x, int y)
{
	mlx_put_image_to_window(game->mlx,
		game->win, (game->assets + asset)->img,
		128 * x, 128 * y);
}

int	try_move(t_game *game, int x, int y)
{
	const int	val = game->map->data[game->map->w * y + x];

	if (x >= game->map->w || y >= game->map->h || x < 0 || y < 0)
		return (0);
	if (val == 2)
	{
		game->map->points += 1;
		game->map->data[game->map->w * y + x] = 1;
	}
	else if (val == 3 && game->map->points == game->map->points_to_finish)
	{
		ft_printf("%i steps! CONGRATULATIONS, TASTY!\n", ++game->map->steps);
		exit(0);
	}
	return (val);
}

int	render(t_game *game, int asset, int *dir, int dir_enum)
{
	if (game->map->x == game->map->exit_x && game->map->y == game->map->exit_y)
		mlx_put_image_to_window(game->mlx,
			game->win, (game->assets + DOOR)->img,
			128 * game->map->x, 128 * game->map->y);
	else
		mlx_put_image_to_window(game->mlx,
			game->win, (game->assets + BACK)->img,
			128 * game->map->x, 128 * game->map->y);
	game->map->x = game->map->x + dir[0];
	game->map->y = game->map->y + dir[1];
	ft_printf("%i\n", ++game->map->steps);
	if (game->map->points == game->map->points_to_finish)
		render_pos(game, DOOR, game->map->exit_x, game->map->exit_y);
	if (asset == 3 && game->map->points != game->map->points_to_finish)
		render_pos(game, CHAR_DOOR, game->map->x, game->map->y);
	else if (asset == 1 || asset == 3)
		render_pos(game, CHAR_BACK + dir_enum,
			game->map->x, game->map->y);
	else if (asset == 2)
		render_pos(game, CHAR_ITEM, game->map->x, game->map->y);
}

int	render_map(t_game *game)
{
	int	i;
	int	j;
	int	val;

	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		while (j < game->map->w)
		{
			val = i * game->map->w + j;
			if (game->map->data[val] == 0)
				render_pos(game, WALL, j, i);
			else if (game->map->data[val] == 1 || game->map->data[val] == 3)
				render_pos(game, BACK, j, i);
			else if (game->map->data[val] == 2)
				render_pos(game, ITEM, j, i);
			j++;
		}
		i++;
	}
	render_pos(game, DOOR, game->map->exit_x, game->map->exit_y);
	render_pos(game, CHAR_FRONT, game->map->x, game->map->y);
}

int	ev(int keycode, t_game *game)
{
	const int	directions[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int			*dir;
	int			dir_enum;
	int			try;

	dir_enum = -1;
	if (keycode == KEY_W)
		dir_enum = 0;
	else if (keycode == KEY_A)
		dir_enum = 1;
	else if (keycode == KEY_S)
		dir_enum = 2;
	else if (keycode == KEY_D)
		dir_enum = 3;
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	dir = (int *)directions[dir_enum];
	render_pos(game, CHAR_BACK + dir_enum, game->map->x, game->map->y);
	try = try_move(game,
			game->map->x + dir[0], game->map->y + dir[1]);
	if (try)
		render(game, try, dir, dir_enum);
	return (0);
}

int	load_assets(t_game *game)
{
	const char	paths[10][50] = {"textures/back.xpm", "textures/wall.xpm",
		"textures/door.xpm", "textures/item.xpm",
		"textures/char_back.xpm", "textures/char_left.xpm",
		"textures/char_front.xpm", "textures/char_right.xpm",
		"textures/char_door.xpm", "textures/char_item.xpm"};
	int			i;

	i = 0;
	while (i < 10)
	{
		game->assets[i].img = mlx_new_image(game->mlx, 128, 128);
		game->assets[i].addr = mlx_get_data_addr(game->assets[i].img,
				&game->assets[i].bits_per_pixel,
				&game->assets[i].line_length, &game->assets[i].endian);
		game->assets[i].img = mlx_xpm_file_to_image(game->mlx, (char *)paths[i],
				&game->assets[i].width, &game->assets[i].height);
		i++;
	}
}

int	dummy_map(t_map *map, char *map_name)
{
	int	i;
	int	j;

	(void)map_name;
	map->w = 7;
	map->h = 7;
	map->points = 0;
	map->points_to_finish = 5;
	map->steps = 0;
	i = 0;
	while (i < 1000)
		map->data[i++] = 0;
	i = 1;
	while (i < map->h - 1)
	{
		j = 1;
		while (j < map->w - 1)
		{
			map->data[i * map->w + j] = 1;
			j++;
		}
		i++;
	}
	map->data[17] = 0;
	map->data[23] = 0;
	map->data[24] = 2;
	map->data[25] = 2;
	map->data[12] = 2;
	map->data[22] = 2;
	map->data[33] = 2;
	map->data[32] = 3;
	map->exit_x = 4;
	map->exit_y = 4;
	map->x = 1;
	map->y = 1;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str++))
		i++;
	return (i);
}

int	process_line(t_map *map, int linenum, char *line)
{
	int	i;
	const int len = ft_strlen(line) - 1;

	i = 0;
	if (linenum == 0)
	{
		map->w = len;
	}
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			map->data[linenum * map->w + i] = 0;
		if (line[i] == '0')
			map->data[linenum * map->w + i] = 1;
		else if (line[i] == 'C')
		{
			map->points_to_finish += 1;
			map->data[linenum * map->w + i] = 2;
		}
		else if (line[i] == 'E')
		{
			map->data[linenum * map->w + i] = 3;
			map->exit_x = i;
			map->exit_y = linenum;
		}
		else if (line[i] == 'P')
		{
			map->data[linenum * map->w + i] = 1;
			map->x = i;
			map->y = linenum;
		}
		i++;
	}
}

int	load_map(t_map *map, char *map_name)
{
	char	*s;
	const int fd = open(map_name, O_RDONLY);
	int	i;

	map->points_to_finish = 0;
	map->steps = 0;
	map->points = 0;
	i = 0;
	if (fd < 0)
		return (-1);
	s = get_next_line(fd);
	while (i < MAX_HEIGHT && s)
	{
		process_line(map, i++, s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	map->h = i;
}

int	main(int argc, char **argv)
{
	t_data		img;
	t_data		imgback;
	t_game		game;
	t_map		map;

	if (argc != 2)
		load_map(&map, "maps/default.ber");
	else
		load_map(&map, argv[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
			map.w * 128, map.h * 128, "GRIBCHIK_GAME");
	game.map = &map;
	load_assets(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, ev, &game);
	mlx_loop(game.mlx);
}
