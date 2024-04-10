/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/10 15:43:32 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


float	ray_to_light(t_vector3 pos, t_vector3 lightpos, t_vector3 normal, t_hitable *list)
{
	t_ray	light;
	float	dot;

	light.dir = vec3_unit(vec3_sub(lightpos, pos));
	light.origin = &pos;
	dot = vec3_dot(light.dir, vec3_unit(normal));
	if (hit_hitable(list, light).hit == 1 && hit_hitable(list, light).distance > 0
		&& hit_hitable(list, light).distance < vec3_length(vec3_sub(pos, lightpos)))
	{
		return (0.3);
	}
	if (dot < 0.1)
		return (0.1);
	return (dot);
}
static int	default_color(t_ray ray)
{
	int			red;
	int			green;
	int			blue;
	float		a;

	a = 0.5 * (vec3_unit(ray.dir).y + 1.0);
	red = (1.0 - a) * 255 + a * 255;
	green = (1.0 - a) * 255 + a * 0.7 * 255;
	blue = (1.0 - a) * 255 + a * 0.5 * 255;
	return ((red << 24) + (green << 16) + (blue << 8) + 255);
}

static float	ray_to_light(t_vector3 pos, t_vector3 lightpos, t_vector3 normal)
{
	t_ray	light;
	float	dot;

	light.dir = vec3_unit(vec3_sub(lightpos, pos));
	light.origin = &pos;
	dot = vec3_dot(light.dir, vec3_unit(normal));
	return (dot);
}

static int	color_add_light(t_hitpoint *hp, t_data *data)
{
	int		c;
	float	dot;
	float	scale;
	
	dot = ray_to_light(hp->pos, data->light.pos, hp->surface_normal_of_hittable);
	scale = dot * data->light.brightness;
	if (scale < data->ambient.brightness)
		scale = data->ambient.brightness;
	c = scale_color(hp->color, scale);
	return (c);
}

static void	set_pixel(t_data *data, int x, int y)
{
	t_hitpoint	hp;
	int color;
	t_ray		ray;

	ray = data->camera.rays[x + y * data->width];
	hp = hit_hitable(data->hitables, ray);
	if (hp.hit)
	{
		c = make_color((unsigned int)hp.color);
		c = scale_color(c, ray_to_light(hp.pos, data->light.pos, hp.surface_normal_of_hittable, data->hitables));
		color = get_color(c);
	}
	else
	{
		color = default_color(ray);
		color = 0xFF;
	}
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
