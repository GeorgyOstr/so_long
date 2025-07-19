/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:09:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/18 01:01:31 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	try_move(t_game *game, int dir_enum, int x, int y)
{
	const int	val = game->map->data[game->map->dim.x * y + x];

	if (x >= game->map->dim.x || y >= game->map->dim.y || x < 0 || y < 0)
		return (0);
	if (game->map->p.x != game->map->exit.x
		|| game->map->p.y != game->map->exit.y)
		render_pos(game, CHAR_BACK + dir_enum + (game->map->steps % 2) * STEP,
			game->map->p.x, game->map->p.y);
	if (val == 2)
	{
		game->map->points += 1;
		game->map->data[game->map->dim.x * y + x] = 1;
	}
	else if (game->map->points == game->map->points_to_finish
		&& game->map->p.x == game->map->exit.x
		&& game->map->p.y == game->map->exit.y)
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
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		dir_enum = 0;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		dir_enum = 1;
	else if (keycode == KEY_S || keycode == KEY_BACK)
		dir_enum = 2;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		dir_enum = 3;
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	dir = (int *)directions[dir_enum];
	try = try_move(game, dir_enum,
			game->map->p.x + dir[0], game->map->p.y + dir[1]);
	if (try)
		render(game, try, dir, dir_enum);
	return (0);
}

int	finish(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
		load_map(&map, "maps/5.ber");
	else
		load_map(&map, argv[1]);
	game.mlx = mlx_init();
	game.map = &map;
	load_assets(&game);
	if (!checker(&game))
		return (0);
	game.win = mlx_new_window(game.mlx, map.dim.x * RES, map.dim.y * RES,
			"GRIBCHIK_GAME");
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, ev, &game);
	mlx_hook(game.win, 17, 0, finish, NULL);
	mlx_loop(game.mlx);
}
