/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:09:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/05 14:57:59 by gostroum         ###   ########.fr       */
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

int	main(void)
{
	t_data		img;
	t_data		imgback;
	int			i;
	t_game		vars;
	int			img_width;
	int			img_height;
	const char	*relative_path = "assets/char_down.xpm";
	const char	*relative_path2 = "assets/back.xpm";
	t_map		map;

	map.w = 5;
	map.h = 5;
	map.points = 0;
	map.points_to_finish = 1;
	i = 0;
	while (i < 1000)
		map.data[i++] = 1;
	map.data[2] = 0;
	map.data[5] = 2;
	map.data[24] = 3;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 640, "GRIBCHIK_GAME");
	vars.map = &map;
	img.img = mlx_new_image(vars.mlx, 128, 128);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.img = mlx_xpm_file_to_image(vars.mlx,
			relative_path, &img_width, &img_height);
	img.img_width = img_width;
	img.img_height = img_height;
	vars.img = &img;
	imgback.img = mlx_new_image(vars.mlx, 128, 128);
	imgback.addr = mlx_get_data_addr(imgback.img,
			&imgback.bits_per_pixel, &imgback.line_length, &imgback.endian);
	imgback.img = mlx_xpm_file_to_image(vars.mlx,
			relative_path2, &img_width, &img_height);
	imgback.img_width = img_width;
	imgback.img_height = img_height;
	vars.back = &imgback;
	mlx_hook(vars.win, 2, 1L << 0, ev, &vars);
	vars.i = 0;
	vars.j = 0;
	mlx_loop(vars.mlx);
}
