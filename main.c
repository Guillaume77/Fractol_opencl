/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 16:27:29 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 18:17:48 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_func_key(int keycode, t_mlx *mlx)
{
	if (keycode < 280 && keycode >= 0)
		if (mlx->f_ptr[keycode])
			mlx->f_ptr[keycode](mlx);
	mlx->draw = 1;
	return (0);
}

int		ft_func_button(int button, int x, int y, t_mlx *mlx)
{
	if (button == Button1 || button == Button4)
	{
		mlx->opencl.zoom *= 1.1;
		mlx->opencl.pos_z_x = (mlx->opencl.pos_z_x + (x / 11)) * 1.1;
		mlx->opencl.pos_z_y = (mlx->opencl.pos_z_y + (y / 11)) * 1.1;
	}
	else if (button == Button2 || button == Button5)
	{
		mlx->opencl.zoom /= 1.1;
		mlx->opencl.pos_z_x = (mlx->opencl.pos_z_x - (x / 11)) / 1.1;
		mlx->opencl.pos_z_y = (mlx->opencl.pos_z_y - (y / 11)) / 1.1;
	}
	mlx->draw = 1;
	return (0);
}

int		ft_motion_mouse(int x, int y, t_mlx *mlx)
{
	if (mlx->active_var)
	{
		mlx->opencl.var_x = ((double)x - (WIDTH / 2)) / mlx->opencl.zoom;
		mlx->opencl.var_y = ((double)y - (HEIGHT / 2)) / mlx->opencl.zoom;
		mlx->draw = 1;
	}
	return (0);
}

int		init_mlx(t_mlx *mlx, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("usage : ./fractol [julia/mandelbrot/...]\n");
		return (-1);
	}
	if (!(mlx->fractal_name = ft_strdup(av[1])))
		return (-1);
	mlx->draw = 1;
	mlx->opencl.it_max = 50;
	mlx->opencl.zoom = 150;
	mlx->opencl.red = 150;
	mlx->opencl.blue = 150;
	mlx->opencl.green = 150;
	mlx->opencl.var_x = 0.0;
	mlx->opencl.var_y = 0.0;
	mlx->active_var = 0;
	mlx->opencl.pos_z_x = 0;
	mlx->opencl.pos_z_y = 0;
	mlx->opencl.move_x = ((double)WIDTH / mlx->opencl.zoom) / 2.0;
	mlx->opencl.move_y = ((double)HEIGHT / mlx->opencl.zoom) / 2.0;
	ft_func_ptr_init(mlx->f_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
    FILE		*fp;
	char		*file_buffer;
    size_t		source_size;
	t_mlx		mlx;
	cl_int		error_code;

    fp = fopen("fractol.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load fractol.cl.\n");
        exit(1);
    }
    file_buffer = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(file_buffer, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
	if ((error_code = cl_create_platform(&mlx.cl)) != CL_SUCCESS)
		return (cl_erreur_log(&mlx.cl, error_code));
	if ((error_code = cl_create_program(&mlx.cl, file_buffer, source_size)) != CL_SUCCESS)
		return (cl_erreur_log(&mlx.cl, error_code));
	if ((init_mlx(&mlx, argc, argv)) == -1)
		return (-1);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, -1, -1, WIDTH, HEIGHT, "FRACTOL");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT, 0xFF0000);
	mlx.data = mlx_get_data_addr(mlx.img, &mlx.opencl.bpp, &mlx.opencl.sizeline, &mlx.opencl.endian);
//	fractol(&mlx);
	mlx_loop_hook(mlx.mlx, &fractol, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, ft_func_key, &mlx);
	mlx_hook(mlx.win, ButtonPress, ButtonPressMask, ft_func_button, &mlx);
	mlx_hook(mlx.win, MotionNotify, ButtonMotionMask, ft_motion_mouse, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
