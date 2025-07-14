/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:59:44 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/15 00:59:13 by gostroum         ###   ########.fr       */
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
	const int	pos = curr.x * map->dim.x + curr.y;

	ans = 0;
	if (curr.x < 0 || curr.y < 0 || curr.x >= map->dim.x || curr.y >= map->dim.x
		|| !map->data[pos] || map->data[pos] == val)
		return (0);
	if (map->data[pos] == 1)
	{
		map->data[pos] = val;
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

	while (i < map->dim.x)
	{
		if (map->data[i] != 0
			&& map->data[map->dim.x * (map->dim.y - 1) + i] != 0)
			return (0);
	}
	while (i < map->dim.y)
	{
		if (map->data[map->dim.x * i] != 0
			&& map->data[map->dim.x * (i + 1) - 1] != 0)
			return (0);
	}
	return (1);
}

int	checker(t_game *game)
{
	const int	side = (side_check(game->map));
	const int	flood = (flood_check(game->map, game->map->p, 10));
	int			i;

	i = 0;
	while (i < game->map->dim.x * game->map->dim.y)
	{
		if (game->map->data[i] == 10)
			game->map->data[i] = 1;
		i++;
	}
	if (!side)
		return (error_map_check());
	if (!flood)
		return (error_path_check());
	return (1);
}
