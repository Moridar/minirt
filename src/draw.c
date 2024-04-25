/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/25 17:13:38 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_pixel(t_data *data, int x, int y)
{
	t_hitpoint		hp;
	unsigned int	color;
	t_ray			ray;

	ray = data->camera.rays[x + y * data->img->width];
	hp = hit_hitable(data->hitables, ray);
	color = 0xFF;
	if (hp.hit)
		color = color_add_light(&hp, data);
	mlx_put_pixel(data->img, x, y, color);
}

void	rerender(t_data *data)
{
	if (data->camera.rays)
		free(data->camera.rays);
	create_camera(data, data->camera.pos,
		data->camera.normal, data->camera.degree);
	ft_printf("Redrawing\n");
	draw(data);
}

void	reposition(t_data *data)
{
	data->img->instances[0].x = (data->mlx->width - (int)data->img->width) / 2;
	data->img->instances[0].y
		= (data->mlx->height - (int)data->img->height) / 2;
}

void	draw(t_data *data)
{
	int		x;
	int		y;
	int		percent;

	data->changed = 0;
	ft_printf("Start drawing...\n");
	percent = 0;
	ft_printf("Drawing [%2d%%]", percent);
	reposition(data);
	x = -1;
	while (++x < (int) data->img->width)
	{
		if (data->changed)
			return ;
		if (x * 100 / (int) data->img->width > percent)
		{
			ft_printf("\rDrawing [%2d%%]", ++percent);
			fflush(stdout);
		}
		y = -1;
		while (++y < (int) data->img->height)
			set_pixel(data, x, y);
	}
	ft_printf("\rDrawing [100%%]\n");
}
