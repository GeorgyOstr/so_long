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

int	try_move(t_map *map, int x, int y)
{
	const int	val = map->data[map->w * y + x];

	if (x >= map->h || y >= map->w || x < 0 || y < 0)
		return (0);
	if (val == 2)
	{
		map->points += 1;
		map->data[map->w * y + x] = 1;
	}
	else if (val == 3 && map->points == map->points_to_finish)
		exit(0);
	return (val);
}

int	ev(int keycode, t_game *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 1731)
	{
		x = 0;
		y = -1;
	}
	if (keycode == 1734)
	{
		x = -1;
		y = 0;
	}
	if (keycode == 1753)
	{
		x = 0;
		y = 1;
	}
	if (keycode == 1751)
	{
		x = 1;
		y = 0;
	}
	x = vars->i + x;
	y = vars->j + y;
	if (try_move(vars->map, x, y))
	{
		mlx_put_image_to_window(vars->mlx,
			vars->win, vars->back->img, 128 * vars->i, 128 * vars->j);
		vars->i = x;
		vars->j = y;
		printf("%i, %i, %i, %i, %i\n", x, y, keycode,
			vars->map->data[vars->map->w * y + x], vars->map->w * y + x);
		mlx_put_image_to_window(vars->mlx,
			vars->win, vars->img->img, 128 * vars->i, 128 * vars->j);
	}
	return (0);
}

int load_assets(t_game *vars)
{
	const char	paths[10][50] = {"assets/back.xpm", "assets/wall.xpm",
                                "assets/door.xpm", "assets/item.xpm",
								"assets/char_down.xpm", "assets/char_left.xpm",
								"assets/char_right.xpm", "assets/char_up.xpm",
								"assets/char_door.xpm", "assets/char_item.xpm"
								};
	t_data		assets[10];
	int			i;

	i = 0;
	while (i < 10)
	{
		assets[i].img = mlx_new_image(vars->mlx, 128, 128);
		assets[i].addr = mlx_get_data_addr(assets[i].img, &(assets[i].bits_per_pixel),
			&(assets[i].line_length), &(assets[i].endian));
		assets[i].img = mlx_xpm_file_to_image(vars->mlx,
			paths[i], &(assets[i].width), &(assets[i].height));
		i++;
	}
	vars->assets = assets;
}

int load_map(t_map *map, char *map_name)
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
}

int	main(void)
{
	t_data		img;
	t_data		imgback;
	int			i;
	t_game		vars;
	t_map		map;
	const char	*relative_path = "assets/char_down.xpm";
	const char	*relative_path2 = "assets/back.xpm";

	load_map(&map, "maps/map.bae");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 640, "GRIBCHIK_GAME");
	vars.map = &map;
	load_assets(&vars);
	img.img = mlx_new_image(vars.mlx, 128, 128);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.img = mlx_xpm_file_to_image(vars.mlx,
			relative_path, &(img.width ), &(img.height));
	vars.img = &img;
	imgback.img = mlx_new_image(vars.mlx, 128, 128);
	imgback.addr = mlx_get_data_addr(imgback.img,
			&imgback.bits_per_pixel, &imgback.line_length, &imgback.endian);
	imgback.img = mlx_xpm_file_to_image(vars.mlx,
			relative_path2, &(imgback.width), &(imgback.height));
	vars.back = &imgback;
	mlx_hook(vars.win, 2, 1L << 0, ev, &vars);
	vars.i = 0;
	vars.j = 0;
	mlx_loop(vars.mlx);
}
