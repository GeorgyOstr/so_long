/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:23:39 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/14 22:23:40 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_file_extension(void)
{
	write(2, "Error\n", 6);
	write(2, "Wrong extension\n", 16);
	return (0);
}

int	error_file_exist(void)
{
	write(2, "Error\n", 6);
	write(2, "No file\n", 8);
	return (0);
}

int	error_map_check(void)
{
	write(2, "Error\n", 6);
	write(2, "Bad map\n", 7);
	return (0);
}

int	error_path_check(void)
{
	write(2, "Error\n", 6);
	write(2, "Bad path\n", 8);
	return (0);
}
