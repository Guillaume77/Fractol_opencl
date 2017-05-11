/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_ptr_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:06:05 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/28 15:33:46 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_func_ptr_init(t_func_ptr *f_ptr)
{
	int		i;

	i = -1;
	while (++i < 280)
		f_ptr[i] = NULL;
	f_ptr[KEY_ESC] = ft_key_esc;
	f_ptr[KEY_LEFT] = ft_key_left;
	f_ptr[KEY_RIGHT] = ft_key_right;
	f_ptr[KEY_DOWN] = ft_key_down;
	f_ptr[KEY_UP] = ft_key_up;
	f_ptr[KEY_R] = ft_key_r;
	f_ptr[KEY_B] = ft_key_b;
	f_ptr[KEY_G] = ft_key_g;
	f_ptr[KEY_SPACE] = ft_key_space;
	f_ptr[KEY_ADD] = ft_key_add;
	f_ptr[KEY_MINUS] = ft_key_minus;
	f_ptr[KEY_TAB] = ft_key_tab;
}
