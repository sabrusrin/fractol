/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:08:40 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 17:49:27 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	get_color(t_fractol *f, int calc_pos[])
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)calc_pos[0] / (double)f->fractal.iter_max;
	r = (int)(f->clr.r * (1 - t) * pow(t, 3) * 255);
	g = (int)(f->clr.g * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(f->clr.b * pow((1 - t), 3) * t * 255);
	return (r << 16 | g << 8 | b);
}

void			*calc_fractol(void *b)
{
	t_fractol	*f;
	t_block		*block;
	int			tmpw;
	int			id;
	int			calc_pos[2];

	block = (t_block*)b;
	f = block->f;
	id = block->id;
	tmpw = f->blocks[id][0];
	while (f->blocks[id][2] < HEIGHT)
	{
		f->blocks[id][0] = tmpw;
		while (f->blocks[id][0] < f->blocks[id][1])
		{
			calc_pos[0] = f->fract(f, id, tmpw);
			calc_pos[1] = (f->blocks[id][0] + (f->blocks[id][2] * WIDTH));
			if (calc_pos[0] < f->fractal.iter_max)
				((int*)f->img.data)[calc_pos[1]] = get_color(f, calc_pos);
			f->blocks[id][0]++;
		}
		f->blocks[id][2]++;
	}
	return ((void*)f);
}

void			fractol_thread(t_fractol *f)
{
	t_block			b[THREADS];
	pthread_t		tid[THREADS];
	pthread_attr_t	attr;
	int				i;

	i = 0;
	pthread_attr_init(&attr);
	while (i < THREADS)
	{
		f->blocks[i][0] = ((double)WIDTH / THREADS) * i;
		f->blocks[i][1] = ((double)WIDTH / THREADS) * (i + 1);
		f->blocks[i][2] = 0;
		b[i].f = f;
		b[i].id = i;
		pthread_create(&tid[i], &attr, calc_fractol, &b[i]);
		++i;
	}
	while (i--)
		pthread_join(tid[i], NULL);
}

void			draw_fractol(t_fractol *f)
{
	ft_bzero(f->img.data, WIDTH * HEIGHT * sizeof(unsigned int));
	mlx_clear_window(f->mlx.iptr, f->mlx.wptr);
	if (!f->help)
	{
		fractol_thread(f);
		mlx_put_image_to_window(f->mlx.iptr, f->mlx.wptr, f->mlx.img, 0, 0);
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, 10, 10,
				0xFFFFFF, "PRESS H TO OPEN HELP MENU");
	}
	else
	{
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, WIDTH / 2 - 20, 20,
				0xFFFFFF, "HELP");
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 40, 0xFFFFFF,
				"move up: KEY_DOWN");
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 60, 0xFFFFFF,
				"move down: KEY_UP");
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 80, 0xFFFFFF,
				"move left: KEY_RIGHT");
		mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 100, 0xFFFFFF,
				"move right: KEY_LEFT");
		print_prompt(f);
	}
}

void			print_prompt(t_fractol *f)
{
	char *str;

	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 120, 0xFFFFFF,
			"stop fractal movements: KEY_M");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 140, 0xFFFFFF,
			"decrease iterations: KEY_S");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 160, 0xFFFFFF,
			"increase iterations: KEY_A");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 180, 0xFFFFFF,
			"zoom in: MOUSE SCROLL_UP");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 200, 0xFFFFFF,
			"zoom out: MOUSE SCROLL_DOWN");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 220, 0xFFFFFF,
			"color palette change: KEY_C");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, 20, 240, 0xFFFFFF,
			"RESET: KEY_R");
	str = ft_itoa(f->fractal.iter_max);
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, WIDTH / 2 - 60, 400,
			0xFFFF00, "Iterations: ");
	mlx_string_put(f->mlx.iptr, f->mlx.wptr, WIDTH / 2 + 50, 400,
			0xFFFF00, str);
	ft_strdel(&str);
}
