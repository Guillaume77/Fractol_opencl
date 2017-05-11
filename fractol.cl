typedef struct s_opencl
{
	int			bpp;
	int			endian;
	int			sizeline;
	unsigned char	red;
	unsigned char	blue;
	unsigned char	green;
	double		pos_z_x;
	double		pos_z_y;
	double		var_x;
	double		var_y;
	double		zoom;
	double		move_x;
	double		move_y;
	int			it_max;
}				t_opencl;

void	mlx_write_data(__global char *pepe, int const x, int const y, int const i, __constant const t_opencl *opencl);
int	ft_color(__constant const t_opencl *opencl,  int const i);

int	ft_color(__constant const t_opencl *opencl,  int const i)
{
    unsigned char	r;
	unsigned char	g;
	unsigned char	b;

    r = (opencl->red * i) <= 0 ? opencl->red : (opencl->red * i);
    g = (opencl->green * i) <= 0 ? opencl->green : (opencl->green * i);
    b = (opencl->blue * i) <= 0 ? opencl->blue : (opencl->blue * i);
	return (((0 & 0xFF) << 24) + ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
}

void	mlx_write_data(__global char *pepe, int const x, int const y, int const i, __constant const t_opencl *opencl)
{
	if (i != opencl->it_max)
		*((__global int *)&pepe[(x * (opencl->bpp / 8)) + (y * opencl->sizeline)]) = ft_color(opencl, i);
	else
		*((__global int *)&pepe[(x * (opencl->bpp / 8)) + (y * opencl->sizeline)]) = 0x00000000;
}

__kernel void julia(__global char *pepe, __constant const t_opencl *opencl)
{
	double4 algo;
    int		i;
	double	tmp;
	double		x = (get_global_id(0) * 250);
	double	const	y = get_global_id(1);
	int	const	width = 250 * (get_global_id(0) + 1);
	
	while (x < width)
	  {
	  i = -1;
	algo.z = (x + opencl->pos_z_x) / opencl->zoom - opencl->move_x;
	algo.w = (y + opencl->pos_z_y) / opencl->zoom - opencl->move_y;
	algo.x = 0.285f + opencl->var_x;
	algo.y = 0.01f + opencl->var_y;
	while (((algo.z * algo.z + algo.w * algo.w) < 4.0f) && (++i < opencl->it_max))
	{
		tmp = algo.z;
        algo.z = algo.z * algo.z - algo.w * algo.w + algo.x;
        algo.w = 2.0f * algo.w * tmp + algo.y;
	}
	   mlx_write_data(pepe, x, y, i, opencl);
	   ++x;
	 }
}

__kernel void mandelbrot(__global char *pepe, __constant const t_opencl *opencl)
{
	double4 algo;
    int		i;
	double	tmp;
	double		x = (get_global_id(0) * 250);
	double	const	y = get_global_id(1);
	int	const	width = 250 * (get_global_id(0) + 1);
	
	while (x < width)
	  {
	  i = -1;
	algo.x = (x + opencl->pos_z_x) / opencl->zoom - opencl->move_x;
	algo.y = (y + opencl->pos_z_y) / opencl->zoom - opencl->move_y;
	algo.z = 0.0f + opencl->var_x;
	algo.w = 0.0f + opencl->var_y;
	while (((algo.z * algo.z + algo.w * algo.w) < 4.0f) && (++i < opencl->it_max))
	{
		tmp = algo.z;
        algo.z = algo.z * algo.z - algo.w * algo.w + algo.x;
        algo.w = 2.0f * algo.w * tmp + algo.y;
	}
	   mlx_write_data(pepe, x, y, i, opencl);
	   ++x;
	 }
}
