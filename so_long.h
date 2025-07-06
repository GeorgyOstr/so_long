/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:06 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/05 14:12:57 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define MAX_WIDTH	60
# define MAX_HEIGHT	30

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int	data[4096];
	int	w;
	int	h;
	int	points;
	int	points_to_finish;
}				t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	assets[10];
	t_map	*map;
	t_data	*img;	
	t_data	*back;	
	int		i;
	int		j;
}				t_game;
#endif
