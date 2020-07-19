/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:50:48 by vdescham          #+#    #+#             */
/*   Updated: 2020/03/02 17:50:49 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void	draw_rgb(t_data *data, t_color *color, int y, int x)
{
	if (data->display.endian == 1)
	{
		data->display.addr[(x * data->display.bpp >> 3)
			+ y * data->display.s_line] = color->r;
		data->display.addr[(x * data->display.bpp >> 3)
			+ 1 + y * data->display.s_line] = color->g;
		data->display.addr[(x * data->display.bpp >> 3)
			+ 2 + y * data->display.s_line] = color->b;
	}
	else
	{
		data->display.addr[(x * data->display.bpp >> 3)
			+ y * data->display.s_line] = color->b;
		data->display.addr[(x * data->display.bpp >> 3)
			+ 1 + y * data->display.s_line] = color->g;
		data->display.addr[(x * data->display.bpp >> 3)
			+ 2 + y * data->display.s_line] = color->r;
	}
}

void	draw_wall(t_data *data, t_tex *tex, int y, int x)
{
	double	darken;

	darken = data->ray.line_height * 3.0 / data->win.height;
	darken = darken > 1 ? 1 : darken;
	darken = darken < 0.4 ? 0.4 : darken;
	data->display.addr[(x * data->display.bpp >> 3)
	+ y * data->display.s_line] =
	(unsigned char)tex->addr[(int)(data->ray.wall_x * tex->width)
		* (tex->bpp >> 3) + (int)((y - data->ray.wall_start * 1.0)
		/ data->ray.line_height * tex->height) * tex->s_line] * darken;
	data->display.addr[(x * data->display.bpp >> 3)
	+ 1 + y * data->display.s_line] =
	(unsigned char)tex->addr[(int)(data->ray.wall_x * tex->width)
		* (tex->bpp >> 3) + 1 + (int)((y - data->ray.wall_start * 1.0)
		/ data->ray.line_height * tex->height) * tex->s_line] * darken;
	data->display.addr[(x * data->display.bpp >> 3)
	+ 2 + y * data->display.s_line] =
	(unsigned char)tex->addr[(int)(data->ray.wall_x * tex->width)
		* (tex->bpp >> 3) + 2 + (int)((y - data->ray.wall_start * 1.0)
		/ data->ray.line_height * tex->height) * tex->s_line] * darken;
}

void	get_tex(t_data *data, int y, int x)
{
	if (data->ray.side == N)
		draw_wall(data, &data->north, y, x);
	else if (data->ray.side == S)
		draw_wall(data, &data->south, y, x);
	else if (data->ray.side == E)
		draw_wall(data, &data->east, y, x);
	else if (data->ray.side == W)
		draw_wall(data, &data->west, y, x);
}

void	draw_sky(t_tex *display, t_tex *tex, int y, int x)
{
	display->addr[(x * display->bpp >> 3) + y * display->s_line] =
	tex->addr[(x % tex->width) * (display->bpp >> 3)
		+ (y % tex->height) * tex->s_line];
	display->addr[(x * display->bpp >> 3) + 1 + y * display->s_line] =
	tex->addr[(x % tex->width) * (display->bpp >> 3)
		+ (y % tex->height) * tex->s_line];
	display->addr[(x * display->bpp >> 3) + 2 + y * display->s_line] =
	tex->addr[(x % tex->width) * (display->bpp >> 3)
		+ (y % tex->height) * tex->s_line];
}

void	draw_tex(int x, t_data *data)
{
	int		y;

	y = 0;
	while (y < (data->ray.wall_start < 0 ? 0 : data->ray.wall_start))
	{
		draw_sky(&data->display, &data->sky, y, x);
		y++;
	}
	while (y < (data->ray.wall_end >= data->win.height
			? data->win.height - 1 : data->ray.wall_end))
	{
		get_tex(data, y, x);
		y++;
	}
	while (y < data->win.height)
	{
		draw_rgb(data, &data->floor, y, x);
		y++;
	}
}
