/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:19:30 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 18:24:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_key_r(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.red = mlx->opencl.red < 255 ? mlx->opencl.red + 1 : 0;
}

void		ft_key_b(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.blue = mlx->opencl.blue < 255 ? mlx->opencl.blue + 1 : 0;
}

void		ft_key_g(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.green = mlx->opencl.green < 255 ? mlx->opencl.green + 1 : 0;
}

void		ft_key_space(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->active_var = mlx->active_var ? 0 : 1;
}

void		ft_key_tab(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.it_max = 50;
	mlx->opencl.zoom = 150;
	mlx->opencl.red = 150;
	mlx->opencl.blue = 150;
	mlx->opencl.green = 150;
	mlx->opencl.var_x = 0.0;
	mlx->opencl.var_y = 0.0;
	mlx->opencl.pos_z_x = 0;
	mlx->opencl.pos_z_y = 0;
	mlx->active_var = 0;
	mlx->opencl.move_x = ((double)WIDTH / mlx->opencl.zoom) / 2.0;
	mlx->opencl.move_y = ((double)HEIGHT / mlx->opencl.zoom) / 2.0;
}
