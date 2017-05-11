/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:28:12 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 14:07:09 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_key_add(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	mlx->opencl.it_max += 10;
	printf("%d\n", mlx->opencl.it_max);
}

void		ft_key_minus(void *arg)
{
	t_mlx *mlx;

	mlx = (t_mlx *)arg;
	if (mlx->opencl.it_max > 10)
		mlx->opencl.it_max -= 10;
}
