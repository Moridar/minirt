/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/05 15:16:06 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
		mlx_put_pixel(data->img, x, y, color);
}

void	draw(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
			set_pixel(data, x, y);
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
