#include "mlx.h"
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	int		img_width;
	int		img_height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;	
	int		i;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ev(int keycode, t_vars *vars)
{
	//int	j;

	//j = 0;
	//while (j < 600)
	//{
	//	my_mlx_pixel_put(vars->img, j, vars->i, 0x00FFF000);
	//	j++;
	//}
	//vars->i++;
	printf("%i, %i\n", vars->img->img_width, vars->img->img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, vars->i++, 0);
	vars->i++;
	return (0);
}

int	main(void)
{
	t_data	img;
	int		i;
	t_vars	vars;
	int		img_width;
	int		img_height;
	const char	*relative_path = "open.xpm";

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	img.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	img.img_width = img_width;
	img.img_height = img_height;
	vars.img = &img;
	mlx_hook(vars.win, 2, 1L<<0, ev, &vars);
	vars.i = 0;
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}
