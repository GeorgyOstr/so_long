/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:08:43 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/13 12:21:07 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_assets(t_game *game)
{
	const char	paths[ASSETS][50] = {"textures/back.xpm", "textures/wall.xpm",
		"textures/door.xpm", "textures/item.xpm",
		"textures/char_back.xpm", "textures/char_left.xpm",
		"textures/char_front.xpm", "textures/char_right.xpm",
		"textures/char_door.xpm", "textures/char_item.xpm",
		"textures/door_open.xpm", "textures/exit.xpm",
		"textures/char_back_1.xpm", "textures/char_left_1.xpm",
		"textures/char_front_1.xpm", "textures/char_right_1.xpm"
	};
	int			i;

	i = 0;
	while (i < ASSETS)
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

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str++))
		i++;
	return (i);
}

int	flood_check(t_map *map, int curr_x, int curr_y)
{
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

int	process_line(t_map *map, int linenum, char *line)
{
	int			i;
	const int	len = ft_strlen(line) - 1;

	i = 0;
	if (linenum == 0)
		map->dim.x = len;
	if (map->dim.x > MAX_WIDTH)
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			map->data[linenum * map->dim.x + i] = 0;
		if (line[i] == '0')
			map->data[linenum * map->dim.x + i] = 1;
		else if (line[i] == 'C')
		{
			map->points_to_finish += 1;
			map->data[linenum * map->dim.x + i] = 2;
		}
		else if (line[i] == 'E')
		{
			map->data[linenum * map->dim.x + i] = 3;
			map->exit.x = i;
			map->exit.y = linenum;
		}
		else if (line[i] == 'P')
		{
			map->data[linenum * map->dim.x + i] = 1;
			map->p.x = i;
			map->p.y = linenum;
		}
		i++;
	}
}

int	load_map(t_map *map, char *map_name)
{
	char		*s;
	const int	fd = open(map_name, O_RDONLY);
	int			i;
	int			res;

	map->points_to_finish = 0;
	map->steps = 0;
	map->points = 0;
	i = 0;
	if (fd < 0)
		return (-1);
	s = get_next_line(fd);
	res = 1;
	while (i < MAX_HEIGHT && s && res)
	{
		res = process_line(map, i++, s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	map->dim.y = i;
	if (get_next_line(fd) || res)
		return (0);
}
