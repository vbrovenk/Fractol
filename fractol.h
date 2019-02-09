/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:08:02 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/01/27 17:08:05 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

# define MANDELBROT 1
# define JULIA 2
# define SHIP 3
# define TRICORN 4
# define JULIA_5 5
# define HALL 6
# define LEAF 7

# define WIDTH 800
# define HEIGHT 800
# define THREADS 8

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

# define MOUSE_PLUS 4
# define MOUSE_MINUS 5
# define PLUS_ITER 24
# define MINUS_ITER 27
# define SPACE 49
# define SHIFT 257
# define BACKSPACE 51
# define HELP 44

// UBUTNTU Buttons
// # define PLUS_ITER 65451
// # define MINUS_ITER 65453

// # define MOUSE_PLUS 4
// # define MOUSE_MINUS 5

typedef	struct	s_fract
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*image;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	int			type_fractal;
	void		*fracts_function;

	int			max_iterations;
	int			color;
	int			start;
	double		min_re;
	double		min_im;
	double		delta;
	int			space_on;

	int			mouse_x;
	int			mouse_y;
	int			help;
}				t_fract;

typedef	struct	s_vars
{
	double		z_re;
	double		z_im;
	double		c_re;
	double		c_im;

	double		factor_re;
	double		factor_im;
	double		tmp;
}				t_vars;

void			reset_params(t_fract *fractol);

void			mandelbrot(t_fract *fractol);
void			julia(t_fract *fractol);
void			julia5_iters(t_fract *fractol, t_vars *vars, int x, int y);
void			burning_ship(t_fract *fractol);
void			hall(t_fract *fractol, t_vars *vars, int x, int y);
void			leaf(t_fract *fractol, t_vars *vars, int x, int y);

void			choose_fractal(t_fract *fractol);
int				choose_color(t_fract *fractol, int iters);
void			init_vars(t_fract *fractol, t_vars *vars);
void			iterations(t_fract *fractol, t_vars *vars, int x, int y);
void			iterations_ship(t_fract *fractol, t_vars *vars, int x, int y);

int				x_exit(void *param);
int				choose_key(int key, t_fract *fractol);
int				zoom_mouse(int key, int x, int y, t_fract *fractol);
int				move_mouse(int x, int y, t_fract *fractol);

int				get_color(t_fract *fractol, int iter);
void			general_loop(t_fract *fractol);
#endif
