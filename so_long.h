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

typedef struct s_data
{
	void	*img;
	int		img_width;
	int		img_height;
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

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;	
	t_data	*back;	
	t_map	*map;
	int		i;
	int		j;
}				t_vars;
#endif
