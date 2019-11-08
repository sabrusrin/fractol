/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:53:24 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 19:15:08 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(void *fr, int id, int iter)
{
	double		zx[2];
	double		zy;
	double		cx;
	double		cy;
	t_fractol	*f;

	f = (t_fractol*)fr;
	iter = 0;
	zx[0] = (f->fractal.posx - WIDTH) / ((double)WIDTH * 2) + 0.25;
	zy = (f->fractal.posy - HEIGHT) / ((double)HEIGHT) + 0.5;
	cx = (double)f->blocks[id][0] * f->fractal.scale + f->fractal.x;
	cy = (double)f->blocks[id][2] * f->fractal.scale + f->fractal.y;
	while ((zx[0] * zx[0] + zy * zy < 4) && iter < f->fractal.iter_max)
	{
		zx[1] = zx[0] * zx[0] - zy * zy + cx;
		zy = 2 * zx[0] * zy + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}

int	julia(void *fr, int id, int iter)
{
	double		zx[2];
	double		zy;
	double		cx;
	double		cy;
	t_fractol	*f;

	f = (t_fractol*)fr;
	iter = 0;
	cx = 4 * ((double)f->fractal.posx / WIDTH - 0.5);
	cy = 4 * ((double)(HEIGHT - f->fractal.posy) / HEIGHT - 0.5);
	zx[0] = (double)f->blocks[id][0] * f->fractal.scale + f->fractal.x;
	zy = (double)f->blocks[id][2] * f->fractal.scale + f->fractal.y;
	while ((zx[0] * zx[0] + zy * zy < 4) && iter < f->fractal.iter_max)
	{
		zx[1] = zx[0] * zx[0] - zy * zy + cx;
		zy = 2 * zx[0] * zy + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}

int	burning_ship(void *fr, int id, int iter)
{
	double		zx[2];
	double		zy;
	double		cx;
	double		cy;
	t_fractol	*f;

	f = (t_fractol*)fr;
	iter = 0;
	zx[0] = (f->fractal.posx - WIDTH) / ((double)WIDTH * 2) + 0.25;
	zy = (f->fractal.posy - HEIGHT) / ((double)HEIGHT) + 0.5;
	cx = (double)f->blocks[id][0] * f->fractal.scale + f->fractal.x;
	cy = (double)f->blocks[id][2] * f->fractal.scale + f->fractal.y;
	while (zx[0] * zx[0] + zy * zy < 4 \
			&& iter < f->fractal.iter_max)
	{
		zx[1] = zx[0] * zx[0] - zy * zy + cx;
		zy = 2 * fabs(zx[0] * zy) + cy;
		zx[0] = fabs(zx[1]);
		iter++;
	}
	return (iter);
}
