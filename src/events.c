/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:01:19 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 19:28:47 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(int x, int y, t_fractol *f)
{
	f->fractal.x = ((double)x * f->fractal.scale + f->fractal.x) -
		((f->fractal.scale / SCALE_FACTOR) / 2);
	f->fractal.x += ((f->fractal.scale / SCALE_FACTOR) / 2) -
		((double)x * (f->fractal.scale / SCALE_FACTOR));
	f->fractal.y = ((double)y * f->fractal.scale + f->fractal.y) -
		((f->fractal.scale / SCALE_FACTOR) / 2);
	f->fractal.y += ((f->fractal.scale / SCALE_FACTOR) / 2) -
		((double)y * (f->fractal.scale / SCALE_FACTOR));
	f->fractal.scale /= SCALE_FACTOR;
	f->fractal.iter_max += 2;
}

void	zoom_out(t_fractol *f)
{
	f->fractal.x = (f->fractal.posx * f->fractal.scale +
		f->fractal.x) - ((f->fractal.scale * SCALE_FACTOR) / 2);
	f->fractal.x += ((f->fractal.scale * SCALE_FACTOR) / 2) -
		(f->fractal.posx * (f->fractal.scale * SCALE_FACTOR));
	f->fractal.y = (f->fractal.posy * f->fractal.scale +
		f->fractal.y) - ((f->fractal.scale * SCALE_FACTOR) / 2);
	f->fractal.y += ((f->fractal.scale * SCALE_FACTOR) / 2) -
		(f->fractal.posy * (f->fractal.scale * SCALE_FACTOR));
	f->fractal.scale *= SCALE_FACTOR;
	f->fractal.iter_max -= (f->fractal.iter_max - 2 >= 30) ? 2 : 0;
}

int		mouse_scroll(int mousecode, int x, int y, t_fractol *f)
{
	if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT && !f->help)
	{
		if (mousecode == MOUSE_UP_SCRLL)
			zoom_in(x, y, f);
		else if (mousecode == MOUSE_DOWN_SCRLL)
			zoom_out(f);
		draw_fractol(f);
	}
	return (0);
}

int		mouse_move(int x, int y, t_fractol *f)
{
	if ((x > 0 && y > 0) && (x < WIDTH && y < HEIGHT)
			&& f->fract != mandelbrot && f->fractal.move && !f->help)
	{
		f->fractal.posx = x;
		f->fractal.posy = y;
		draw_fractol(f);
	}
	return (0);
}

int		other_key_events(int keycode, t_fractol *f)
{
	if (keycode == KEY_MINUS && !f->help)
		zoom_out(f);
	else if (keycode == KEY_S && !f->help)
		f->fractal.iter_max -= (f->fractal.iter_max - 5 >= 2) ? 5 : 0;
	else if (keycode == KEY_A && !f->help)
		f->fractal.iter_max += 5;
	else if (keycode == KEY_R && !f->help)
		init_fractol(f);
	else if (keycode == KEY_M && !f->help)
		f->fractal.move = (f->fractal.move) ? 0 : 1;
	else if (keycode == KEY_C && !f->help)
	{
		f->clr.r = rand() % (0xFF + 0x01);
		f->clr.g = rand() % (0xFF + 0x01);
		f->clr.b = rand() % (0xFF + 0x01);
	}
	else if (keycode == KEY_H)
		f->help = (f->help) ? 0 : 1;
	return (0);
}
