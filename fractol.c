/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:06:08 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 14:03:19 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include "fractol.h"

int		fractol(t_mlx *mlx)
{
	cl_int		error;
	t_noyau		kernel;
	t_cl_buffer	cl_b;

	if (mlx->draw == 1)
	{
		if ((error = cl_create_kernel(mlx, &kernel, &cl_b)) != CL_SUCCESS)
		{
			printf("%d\n", error);
			return (-1);
		}
		if ((error = cl_read_buffer(mlx, &kernel, &cl_b)) != CL_SUCCESS)
		{
			printf("%d\n", error);
			return (-1);
		}
		clReleaseMemObject(cl_b.data);
		clReleaseMemObject(cl_b.opencl);
		clReleaseKernel(kernel.noyau);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	mlx->draw = 0;
	return (0);
}
