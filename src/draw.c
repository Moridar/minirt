/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/27 02:48:15 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rv_setdata(t_data *data)
{
	t_vector3	normal;

	normal = data->camera.normal;
	normal.y = 0;
	normal = vec3_unit(normal);
	data->raycfg.yaw.axis = vec3_cross(((t_vector3){0, 0, 1}), normal);
	data->raycfg.yaw.cos = vec3_dot((t_vector3){0, 0, 1}, normal);
	data->raycfg.yaw.sin = sin(acos(data->raycfg.yaw.cos));
	data->raycfg.yaw.invcos = 1.0f - data->raycfg.yaw.cos;
	data->raycfg.pitch.axis = vec3_cross(normal, (t_vector3){0, 1, 0});
	data->raycfg.pitch.sin = data->camera.normal.y;
	data->raycfg.pitch.cos = cos(asin(data->raycfg.pitch.sin));
	data->raycfg.pitch.invcos = 1.0f - data->raycfg.pitch.cos;
	data->raycfg.vecz = (data->img->width / 2)
		/ tan(data->camera.degree * M_PI / 360);
}

static void	set_pixel(t_data *data, int x, int y)
{
	t_hitpoint		hp;
	unsigned int	color;
	t_ray			ray;

	ray = create_ray(data, x, y);
	hp = hit_hitable(data->hitables, ray);
	color = 0xFF;
	if (hp.hit)
		color = color_add_light(&hp, data);
	mlx_put_pixel(data->img, x, y, color);
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
	percent = 0;
	ft_printf("Start drawing...\n");
	printf("Resolution: %u, %u\n", data->img->width, data->img->height);
	ft_printf("Drawing [%2d%%]", percent);
	rv_setdata(data);
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
