/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:02:07 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/12 23:57:27 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_pos(t_game *game, int asset, int x, int y)
{
	mlx_put_image_to_window(game->mlx,
		game->win, (game->assets + asset)->img,
		128 * x, 128 * y);
}

int	render(t_game *game, int asset, int *dir, int dir_enum)
{
	if (game->map->p.x == game->map->exit.x
		&& game->map->p.y == game->map->exit.y && asset == 3)
		render_pos(game, CHAR_DOOR, game->map->p.x, game->map->p.y);
	else if (game->map->p.x == game->map->exit.x
		&& game->map->p.y == game->map->exit.y && (asset == 2 || asset == 1))
		render_pos(game, DOOR, game->map->p.x, game->map->p.y);
	else
		render_pos(game, BACK, game->map->p.x, game->map->p.y);
	game->map->p.x = game->map->p.x + dir[0];
	game->map->p.y = game->map->p.y + dir[1];
	ft_printf("%i\n", ++game->map->steps);
	if (game->map->points == game->map->points_to_finish && asset == 2)
		render_pos(game, DOOR_OPEN, game->map->exit.x, game->map->exit.y);
	if (game->map->points == game->map->points_to_finish && asset == 3)
	{
		ft_printf("%i steps! CONGRATULATIONS, TASTY!\n", game->map->steps);
		render_pos(game, EXIT, game->map->exit.x, game->map->exit.y);
	}
	else if (asset == 3 && game->map->points != game->map->points_to_finish)
		render_pos(game, CHAR_DOOR, game->map->p.x, game->map->p.y);
	else if (asset == 1 || asset == 3)
		render_pos(game, CHAR_BACK + dir_enum + (game->map->steps % 2) * STEP,
			game->map->p.x, game->map->p.y);
	else if (asset == 2)
		render_pos(game, CHAR_ITEM, game->map->p.x, game->map->p.y);
}

int	render_map(t_game *game)
{
	int	i;
	int	j;
	int	val;

	i = 0;
	while (i < game->map->dim.y)
	{
		j = 0;
		while (j < game->map->dim.x)
		{
			val = i * game->map->dim.x + j;
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
	render_pos(game, DOOR, game->map->exit.x, game->map->exit.y);
	render_pos(game, CHAR_FRONT, game->map->p.x, game->map->p.y);
}
