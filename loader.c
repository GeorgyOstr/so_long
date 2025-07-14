/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:08:43 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/13 21:36:32 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_assets(t_game *game)
{
	const char	paths[ASSETS][50] = {"textures/wall.xpm", "textures/back.xpm",
		"textures/item.xpm", "textures/door.xpm",
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
				&game->assets[i].bits_per_pixel, &game->assets[i].line_length,
				&game->assets[i].endian);
		game->assets[i].img = mlx_xpm_file_to_image(game->mlx, (char *)paths[i],
				&game->assets[i].width, &game->assets[i].height);
		i++;
	}
}

int	process_line(t_map *map, int linenum, char *line)
{
	int			i;
	const int	len = ft_strlen(line) - 1;

	i = 0;
	if (linenum == 0)
		map->dim.x = len;
	if (map->dim.x > MAX_WIDTH || len != map->dim.x)
		return (error_map_check());
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			map->data[linenum * map->dim.x + i] = 0;
		else if (line[i] == '0')
			map->data[linenum * map->dim.x + i] = 1;
		else if (line[i] == 'C')
		{
			map->points_to_finish += 1;
			map->data[linenum * map->dim.x + i] = 2;
		}
		else if (line[i] == 'E')
		{
			map->data[linenum * map->dim.x + i] = 3;
			if (map->exit.x >= 0)
				return (error_map_check());
			map->exit = (t_pos){i, linenum};
		}
		else if (line[i] == 'P')
		{
			map->data[linenum * map->dim.x + i] = 1;
			if (map->p.x >= 0)
				return (error_map_check());
			map->p = (t_pos){i, linenum};
		}
		else
			return (error_map_check());
		i++;
	}
	return (1);
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
	map->p.x = -1;
	map->exit.x = -1;
	i = 0;
	if (check_extension(map_name))
		return (error_file_extension());
	if (fd < 0)
		return (error_file_exist());
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
	if (get_next_line(fd) || !res || map->p.x < 0 || map->exit.x < 0)
		return (error_map_check());
}
