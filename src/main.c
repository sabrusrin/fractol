/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:27:50 by chermist          #+#    #+#             */
/*   Updated: 2019/10/31 19:32:12 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		set_fractol(t_fractol *f, char *opt)
{
	if (!ft_strcmp(opt, "mandelbrot"))
		f->fract = &mandelbrot;
	else if (!ft_strcmp(opt, "julia"))
		f->fract = &julia;
	else if (!ft_strcmp(opt, "multi_julia"))
		f->fract = &multi_julia;
	else if (!ft_strcmp(opt, "perpendicular_burning_ship"))
		f->fract = &chicken;
	else if (!ft_strcmp(opt, "burning_ship"))
		f->fract = &burning_ship;
	else if (!ft_strcmp(opt, "compass"))
		f->fract = &compass;
	else if (!ft_strcmp(opt, "mandelbar"))
		f->fract = &mandelbar;
	else if (!ft_strcmp(opt, "orth_mandl"))
		f->fract = &orth_mandl;
	else
	{
		ft_putstr("Usage:	./fractol [option]\n");
		ft_putstr("\tmandelbrot\n\tjulia\n\tmulti_julia\n");
		ft_putstr("\tperpendicular_burning_ship\n\tburning_ship\n");
		ft_putstr("\tcompass\n\tmandelbar\n\torth_mandl\n");
		exit(0);
	}
	return (1);
}

void	init_fractol(t_fractol *f)
{
	f->fractal.x = -2.6;
	f->fractal.y = -1.2;
	f->fractal.move = 0;
	f->fractal.iter_max = 64;
	if ((f->fract == julia || f->fract == multi_julia)
			&& (f->fractal.move = 1))
		f->fractal.x = -1.8;
	if (f->fract == burning_ship)
	{
		f->fractal.x = -2.24;
		f->fractal.y = -1.8;
		f->fractal.iter_max = 125;
	}
	if (f->fract == compass || f->fract == orth_mandl
			|| f->fract == mandelbar)
		f->fractal.x = -2.22;
	if (f->fract == chicken)
		f->fractal.x = -1.44;
	f->fractal.posx = WIDTH / 2;
	f->fractal.posy = HEIGHT / 2;
	f->fractal.scale = 0.005;
	f->clr.r = 106;
	f->clr.g = 52;
	f->clr.b = 3;
	f->help = 0;
}

int		key_event(int keycode, t_fractol *f)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_image(f->mlx.iptr, f->mlx.img);
		mlx_destroy_window(f->mlx.iptr, f->mlx.wptr);
		exit(0);
	}
	else if (keycode == KEY_UP && !f->help)
		f->fractal.y -= (double)4 * f->fractal.scale;
	else if (keycode == KEY_LEFT && !f->help)
		f->fractal.x -= (double)4 * f->fractal.scale;
	else if (keycode == KEY_DOWN && !f->help)
		f->fractal.y += (double)4 * f->fractal.scale;
	else if (keycode == KEY_RIGHT && !f->help)
		f->fractal.x += (double)4 * f->fractal.scale;
	else if (keycode == KEY_EQUAL && !f->help)
		zoom_in(WIDTH / 2, HEIGHT / 2, f);
	else
		other_key_events(keycode, f);
	draw_fractol(f);
	return (0);
}

int		red_button(t_fractol *f)
{
	mlx_destroy_image(f->mlx.iptr, f->mlx.img);
	mlx_destroy_window(f->mlx.iptr, f->mlx.wptr);
	exit(0);
}

int		main(int ac, char **av)
{
	t_fractol	f;
	const char	*str;

	str = NULL;
	if (ac == 2)
	{
		set_fractol(&f, av[1]);
		f.mlx.iptr = mlx_init();
		f.mlx.wptr = mlx_new_window(f.mlx.iptr, WIDTH, HEIGHT, "fractol");
		f.mlx.img = mlx_new_image(f.mlx.iptr, WIDTH, HEIGHT);
		f.img.data = mlx_get_data_addr(f.mlx.img, &f.img.bpp,
				&f.img.size, &f.img.endian);
		init_fractol(&f);
		draw_fractol(&f);
		mlx_hook(f.mlx.wptr, 2, 0, key_event, &f);
		mlx_hook(f.mlx.wptr, 4, 0, mouse_scroll, &f);
		mlx_hook(f.mlx.wptr, 6, 0, mouse_move, &f);
		mlx_hook(f.mlx.wptr, 17, 0, red_button, &f);
		mlx_loop(f.mlx.iptr);
	}
	else
		set_fractol(&f, "exit");
	return (0);
}
