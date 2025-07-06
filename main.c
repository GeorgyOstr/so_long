/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:09:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/06 00:12:41 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_pos(t_game *game, int asset, int x, int y)
{
	mlx_put_image_to_window(game->mlx,
		game->win, (game->assets + asset)->img,
		128 * x, 128 * y);
}

int	try_move(t_game *game, t_map *map, int x, int y)
{
	const int	val = map->data[map->w * y + x];

	if (x >= map->h || y >= map->w || x < 0 || y < 0)
		return (0);
	if (val == 2)
	{
		map->points += 1;
		map->data[map->w * y + x] = 1;
		if (map->points == map->points_to_finish)
			render_pos(game, DOOR, map->exit_x, map->exit_y);
	}
	else if (val == 3 && map->points == map->points_to_finish)
		exit(0);
	return (val);
}

int	render(t_game *game, int asset, int *dir, int dir_enum)
{
	mlx_put_image_to_window(game->mlx,
		game->win, (game->assets + BACK)->img, 128 * game->i, 128 * game->j);
	game->i = game->i + dir[0];
	game->j = game->j + dir[1];
	printf("%i, %i, %i, %i\n", game->i, game->j,
		game->map->data[game->map->w * game->j + game->i],
		game->map->w * game->j + game->i);
	if (asset == 1)
		render_pos(game, CHAR_UP + dir_enum, game->i, game->j);
	else if (asset == 2)
		render_pos(game, CHAR_ITEM, game->i, game->j);
	else if (asset == 3)
		render_pos(game, CHAR_DOOR, game->i, game->j);
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
	render_pos(game, CHAR_DOWN, game->map->start_x, game->map->start_y);
}

int	ev(int keycode, t_game *game)
{
	const int	directions[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int			*dir;
	int			dir_enum;
	int			try;

	dir_enum = 0;
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
	try = try_move(game, game->map, game->i + dir[0], game->j + dir[1]);
	if (try)
		render(game, try, dir, dir_enum);
	return (0);
}

int	load_assets(t_game *game)
{
	const char	paths[10][50] = {"assets/back.xpm", "assets/wall.xpm",
		"assets/door.xpm", "assets/item.xpm",
		"assets/char_up.xpm", "assets/char_left.xpm",
		"assets/char_down.xpm", "assets/char_right.xpm",
		"assets/char_door.xpm", "assets/char_item.xpm"};
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

int	load_map(t_map *map, char *map_name)
{
	int	i;

	(void)map_name;
	map->w = 5;
	map->h = 5;
	map->points = 0;
	map->points_to_finish = 1;
	i = 0;
	while (i < 1000)
		map->data[i++] = 1;
	map->data[2] = 0;
	map->data[5] = 2;
	map->data[24] = 3;
	map->exit_x = 4;
	map->exit_y = 4;
	map->start_x = 0;
	map->start_y = 0;
}

int	main(void)
{
	t_data		img;
	t_data		imgback;
	t_game		game;
	t_map		map;

	load_map(&map, "maps/map.bae");
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 640, "GRIBCHIK_GAME");
	game.map = &map;
	load_assets(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, ev, &game);
	game.i = 0;
	game.j = 0;
	mlx_loop(game.mlx);
}
