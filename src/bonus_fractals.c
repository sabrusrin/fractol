/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:30:06 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 19:24:57 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	chicken(void *fr, int id, int iter)
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
		zx[1] = zx[0];
		zx[0] = zx[0] * zx[0] - zy * zy - cx;
		zy = -2.0 * zx[1] * fabs(zy) - cy;
		iter++;
	}
	return (iter);
}

int	multi_julia(void *fr, int id, int iter)
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
		zx[1] = pow((zx[0] * zx[0] + zy * zy), 2) *
			cos(4 * atan2(zy, zx[0])) + cx;
		zy = pow((zx[0] * zx[0] + zy * zy), 2) * sin(4 * atan2(zy, zx[0])) + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}

int	compass(void *fr, int id, int iter)
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
		zx[1] = -1 * (zx[0] * zx[0] - (zy * zy * 3)) * zx[0] + cx + 0.42;
		zy = ((zx[0] * zx[0] * 3) - zy * zy) * zy + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}

int	mandelbar(void *fr, int id, int iter)
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
		zy = -2 * fabs(zx[0]) * zy + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}

int	orth_mandl(void *fr, int id, int iter)
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
		zy = -2 * zx[0] * zy + cy;
		zx[0] = zx[1];
		iter++;
	}
	return (iter);
}
