/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:07:59 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 16:35:20 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		cl_create_buffer(t_mlx *mlx, t_cl_buffer *cl_b)
{
	cl_int	error_code;

	// Association des variables de données avec le tampon d'échange
	cl_b->data = clCreateBuffer(mlx->cl.contexte,
								  0,
								sizeof(char) * (HEIGHT * mlx->opencl.sizeline + WIDTH * (mlx->opencl.bpp / 8)),
								NULL,
								  &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);
	cl_b->opencl = clCreateBuffer(mlx->cl.contexte,
								  CL_MEM_READ_ONLY,
								  sizeof(mlx->opencl),
								  NULL,
								  &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);
	return (0);
}

int		cl_create_kernel(t_mlx *mlx, t_noyau *kernel, t_cl_buffer *cl_b)
{
	cl_int		error_code;

	if ((error_code = cl_create_buffer(mlx, cl_b)) != CL_SUCCESS)
		return (error_code);
	// Construire le noyau
	kernel->noyau = clCreateKernel(mlx->cl.programme, mlx->fractal_name, &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);
	// Associer les tampons d'échanges avec
	// les arguments des fonctions à paralléliser
	if ((clSetKernelArg(kernel->noyau,
						0,
						sizeof(cl_b->data),
						&cl_b->data)) != CL_SUCCESS)
		return (error_code);
	if ((clSetKernelArg(kernel->noyau,
						1,
						sizeof(cl_b->opencl),
						&cl_b->opencl)) != CL_SUCCESS)
		return (error_code);
    error_code = clEnqueueWriteBuffer(mlx->cl.file_execution, cl_b->data, CL_TRUE, 0,
							  sizeof(char) * (HEIGHT * mlx->opencl.sizeline + WIDTH * (mlx->opencl.bpp / 8)), mlx->data, 0, NULL, NULL);
	if (error_code != CL_SUCCESS)
		return (error_code);
    error_code = clEnqueueWriteBuffer(mlx->cl.file_execution, cl_b->opencl, CL_TRUE, 0,
									  sizeof(mlx->opencl), (void *)&mlx->opencl, 0, NULL, NULL);
	if (error_code != CL_SUCCESS)
		return (error_code);
	return (0);
}

int		cl_read_buffer(t_mlx *mlx, t_noyau *kernel, t_cl_buffer *cl_b)
{
	cl_int			error;
	size_t		global_item_size[] = {4, 1000};
//	size_t		local_item_size = 0;

	error = clEnqueueNDRangeKernel(mlx->cl.file_execution,
										kernel->noyau,
										2,
										NULL,
								global_item_size,
								   NULL,
										0,
										NULL,
								   NULL);
	if (error != CL_SUCCESS)
	{
		printf("%d\n", error);
		return (-1);
	}
	clFinish(mlx->cl.file_execution);
	// Récupération des résultats dans le tampon
	error = clEnqueueReadBuffer(mlx->cl.file_execution,
						cl_b->data,
						CL_TRUE,
						0,
						sizeof(char) * (HEIGHT * mlx->opencl.sizeline + WIDTH * (mlx->opencl.bpp / 8)),
						mlx->data,
						0,
						NULL,
						NULL);
	if (error != CL_SUCCESS)
	{
		printf("%d\n", error);
		return (-1);
	}
	return (0);
}
