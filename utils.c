/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:14:08 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/09 12:13:49 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

void		ft_key_esc(void *arg)
{
	arg++;
	exit(1);
}

void		ft_key_left(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.move_x -= 10 / mlx->opencl.zoom;
}

void		ft_key_right(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.move_x += 10 / mlx->opencl.zoom;
}

void		ft_key_down(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.move_y += 10 / mlx->opencl.zoom;
}

void		ft_key_up(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.move_y -= 10 / mlx->opencl.zoom;
}
