/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/07 23:04:34 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_pixel(t_data *data, int x, int y)
{
	int		color;
	int		red;
	int		green;
	int		blue;
	float	a;

	color = hit_hitable(data->hitables, data->camera.rays[x + y * data->width]);
	if (color)
	{
		mlx_put_pixel(data->img, x, y, color);
		return ;
	}
	a = 0.5 * (vec3_unit(data->camera.rays[x + y * data->width].dir).y + 1.0);
	red = (1.0 - a) * 255 + a * 255;
	green = (1.0 - a) * 255 + a * 0.7 * 255;
	blue = (1.0 - a) * 255 + a * 0.5 * 255;
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	mlx_put_pixel(data->img, x, y, color);
}

void	draw(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
			set_pixel(data, x, y);
	}
}
