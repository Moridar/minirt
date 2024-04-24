/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/24 23:21:54 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_pixel(t_data *data, int x, int y)
{
	t_hitpoint		hp;
	unsigned int	color;
	t_ray			ray;

	ray = data->camera.rays[x + y * data->width];
	hp = hit_hitable(data->hitables, ray);
	color = 0xFF;
	if (hp.hit)
		color = color_add_light(&hp, data);
	mlx_put_pixel(data->img, x, y, color);
}

void	draw(t_data *data)
{
	int		x;
	int		y;
	int		percent;

	ft_printf("Start drawing...\n");
	percent = 0;
	ft_printf("Drawing [%2d%%]", percent);
	x = -1;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	while (++x < data->width)
	{
		if (x * 100 / data->width > percent)
		{
			ft_printf("\rDrawing [%2d%%]", ++percent);
			fflush(stdout);
		}
		y = -1;
		while (++y < data->height)
			set_pixel(data, x, y);
	}
	ft_printf("\rDrawing [100%%]\n");
}
