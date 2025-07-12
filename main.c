/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:09:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/12 23:55:59 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	try_move(t_game *game, int dir_enum, int x, int y)
{
	const int	val = game->map->data[game->map->w * y + x];

	if (x >= game->map->w || y >= game->map->h || x < 0 || y < 0)
		return (0);
	if (game->map->x != game->map->exit_x
        || game->map->y != game->map->exit_y)
		render_pos(game, CHAR_BACK + dir_enum, game->map->x, game->map->y);
	if (val == 2)
	{
		game->map->points += 1;
		game->map->data[game->map->w * y + x] = 1;
	}
	else if (game->map->points == game->map->points_to_finish
		&& game->map->x == game->map->exit_x
		&& game->map->y == game->map->exit_y)
		exit(0);
	return (val);
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
	try = try_move(game, dir_enum,
			game->map->x + dir[0], game->map->y + dir[1]);
	if (try)
		render(game, try, dir, dir_enum);
	return (0);
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
