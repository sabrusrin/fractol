/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:32:22 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 19:28:48 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 720
# define HEIGHT 480
# define THREADS 16
# define SCALE_LIMIT 500000000
# define SCALE_FACTOR	1.09

# define MOUSE_UP_SCRLL		4
# define MOUSE_DOWN_SCRLL	5

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# include "mlx.h"
# include "libft.h"
# include "mlx_keys.h"

typedef struct	s_clr
{
	int			r;
	int			g;
	int			b;
}				t_clr;

typedef struct	s_mlx
{
	void		*iptr;
	void		*wptr;
	void		*img;
}				t_mlx;

typedef struct	s_img
{
	char		*data;
	int			size;
	int			endian;
	int			bpp;
}				t_img;

typedef struct	s_fractal
{
	int			max_iteration;
	int			iter_max;
	int			iter;
	int			calc[WIDTH][HEIGHT];
	int			limit;
	int			move;
	double		scale;
	double		posx;
	double		posy;
	double		x;
	double		y;
	double		width;
	double		height;
}				t_fractal;

typedef struct	s_fractol
{
	t_mlx		mlx;
	t_img		img;
	t_fractal	fractal;
	int			(*fract)(void *fractol, int id, int iter);
	t_clr		clr;
	int			blocks[THREADS][3];
	int			help;
}				t_fractol;

typedef struct	s_block
{
	t_fractol	*f;
	int			id;
}				t_block;

void			init_fractol(t_fractol *f);
void			draw_fractol(t_fractol *f);

int				mandelbrot(void *f, int id, int iter);
int				julia(void	*f, int id, int iter);
int				multi_julia(void	*fr, int id, int iter);
int				chicken(void *fr, int id, int iter);
int				burning_ship(void *fr, int id, int iter);
int				compass(void *fr, int id, int iter);
int				mandelbar(void *fr, int id, int iter);
int				orth_mandl(void *fr, int id, int iter);

int				mouse_scroll(int mousecode, int x, int y, t_fractol *f);
int				mouse_move(int x, int y, t_fractol *f);
int				other_key_events(int keycode, t_fractol *f);

void			zoom_in(int x, int y, t_fractol *f);
void			zoom_out(t_fractol *f);

void			print_prompt(t_fractol *f);

#endif
