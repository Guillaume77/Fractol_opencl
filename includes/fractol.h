/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:05:34 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 13:59:17 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

# include "../minilibx_macos/mlx.h"
# include "libft.h"
# include <stdio.h>
# include <pthread.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>
# define ABS(x) ((x) < 0 ? -(x) : (x))
# define MAX(x, y) ((x) <= (y) ? (y) : (x))
# define WIDTH 1000
# define HEIGHT 1000
# define COLOR 0xFF
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_R 15
# define KEY_B 11
# define KEY_G 5
# define KEY_SPACE 49
# define KEY_ADD 69
# define KEY_MINUS 78
# define KEY_P_UP 121
# define KEY_P_DOWN 116
# define KEY_TAB 48
# define NB_THREADS 16
# define MAX_SOURCE_SIZE 100000

typedef struct				s_cl
{
	cl_platform_id			plateformeID;
	cl_uint					qtePlateformes;
	cl_device_id			TOUS_peripheriqueID;
	cl_uint					TOUS_qtePeripheriques;
	cl_context				contexte;
	cl_context_properties	proprietes[3];
	cl_command_queue		file_execution;
	cl_program				programme;
}							t_cl;

typedef struct				s_noyau
{
	cl_kernel				noyau;
	char					*function_name;
	int						*inputData;
	size_t					inputDataSize;
	int						*outputData;
	size_t					outputDataSize;
	cl_mem					input_buffer;
	cl_mem					output_buffer;
}							t_noyau;

typedef struct	s_thread
{
	int			i;
	void		*arg;
}				t_thread;

typedef	void		(*t_func_ptr)(void *arg);


typedef struct	s_opencl
{
	cl_int			bpp;
	cl_int			endian;
	cl_int			sizeline;
	cl_uchar		red;
	cl_uchar		blue;
	cl_uchar		green;
	cl_double		pos_z_x;
	cl_double		pos_z_y;
	cl_double		var_x;
	cl_double		var_y;
	cl_double		zoom;
	cl_double		move_x;
	cl_double		move_y;
	cl_int			it_max;
}				t_opencl;

typedef struct	s_mlx
{
	t_cl		cl;
	t_opencl	opencl;
	void		*mlx;
	void		*win;
	void		*img;
	void		*data;
	char		draw;
	char		active_var;
	char		*fractal_name;
	t_func_ptr	f_ptr[280];
	t_thread	thread[NB_THREADS];
	pthread_t	pthread[NB_THREADS];
}				t_mlx;

typedef struct	s_cl_buffer
{
	cl_mem		data;
	cl_mem		opencl;
	cl_mem		sizeline;
	cl_mem		red;
	cl_mem		blue;
	cl_mem		green;
	cl_mem		pos_z_x;
	cl_mem		pos_z_y;
	cl_mem		var_x;
	cl_mem		var_y;	
	cl_mem		zoom;
	cl_mem		move_x;
	cl_mem		move_y;
	cl_mem		it_max;
}				t_cl_buffer;

int				fractol(t_mlx *mlx);
void			ft_func_ptr_init(t_func_ptr *f_ptr);
void			ft_key_esc(void *arg);
void			ft_key_left(void *arg);
void			ft_key_right(void *arg);
void			ft_key_down(void *arg);
void			ft_key_up(void *arg);
void			ft_key_r(void *arg);
void			ft_key_b(void *arg);
void			ft_key_g(void *arg);
void			ft_key_space(void *arg);
void			ft_key_tab(void *arg);
void			ft_key_add(void *arg);
void			ft_key_minus(void *arg);
int				cl_create_program(t_cl *cl, const char *file_buffer, size_t source_size);
int				cl_create_platform(t_cl *cl);
int				cl_erreur_log(t_cl *cl, cl_int error_code);
int				cl_create_kernel(t_mlx *mlx, t_noyau *kernel, t_cl_buffer *cl_b);
int				cl_read_buffer(t_mlx *mlx, t_noyau *kernel, t_cl_buffer *cl_b);

#endif
