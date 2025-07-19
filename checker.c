/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:59:44 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/18 01:02:23 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_val(int val)
{
	if (val < 4)
		return (0);
	return (1);
}

int	check_extension(char *str)
{
	const int	len = ft_strlen(str);

	if (len < 5 || ft_strncmp(str, ".ber", 4))
		return (0);
	return (1);
}

int	flood_check(t_map *map, t_pos curr, const int val)
{
	int			ans;
	const int	pos = curr.y * map->dim.x + curr.x;

	ans = 0;
	if (curr.x < 0 || curr.y < 0 || curr.x >= map->dim.x || curr.y >= map->dim.x
		|| !map->data[pos] || map->data[pos] == val)
		return (0);
	if (map->data[pos] == 1 || map->data[pos] == 2)
	{
		map->data[pos] += val;
		ans |= flood_check(map, (t_pos){curr.x + 1, curr.y}, val);
		ans |= flood_check(map, (t_pos){curr.x, curr.y + 1}, val);
		ans |= flood_check(map, (t_pos){curr.x - 1, curr.y}, val);
		ans |= flood_check(map, (t_pos){curr.x, curr.y - 1}, val);
	}
	if (map->data[pos] == 3)
		return (1);
	return (ans);
}

int	side_check(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->dim.x)
	{
		if (map->data[i] != 0
			|| map->data[map->dim.x * (map->dim.y - 1) + i] != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < map->dim.y)
	{
		if (map->data[map->dim.x * i] != 0
			|| map->data[map->dim.x * (i + 1) - 1] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	checker(t_game *game)
{
	int			i;
	int			sizex;
	int			sizey;

	i = 0;
	if (!game->map->points_to_finish)
		error_map_check();
	if (!side_check(game->map))
		error_map_check();
	if (!flood_check(game->map, game->map->p, 10))
		error_path_check();
	while (i < game->map->dim.x * game->map->dim.y)
	{
		if (game->map->data[i] == 11 || game->map->data[i] == 12)
			game->map->data[i] -= 10;
		i++;
	}
	mlx_get_screen_size(game->mlx, &sizex, &sizey);
	if (sizex / RES < game->map->dim.x || sizey / RES < game->map->dim.y)
		error_map_check();
	return (1);
}
