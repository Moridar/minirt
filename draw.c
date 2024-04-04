/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/04 14:24:04 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	set_pixel(t_data *data, int x, int y)
{
	int	color;
	int	red;
	int	green;
	int	blue;

	red = x * 255 / data->width;
	green = y * 255 / data->height;
	blue = 0;
	color = (red << 16) + (green << 8) + blue;
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		my_mlx_pixel_put(data, x, y, color);
}

void	draw(t_data *data)
{
	int		x;
	int		y;

	mlx_clear_window(data->mlx, data->win);
	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
			set_pixel(data, x, y);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
