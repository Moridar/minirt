/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:03:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/11 12:50:21 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	ray_to_light(t_vector3 pos, t_vector3 lightpos)
{
	t_ray	light;

	light.dir = vec3_unit(vec3_sub(lightpos, pos));
	light.origin = &pos;

	return (light);
}
static float get_diffuse_scale(t_data *data, t_hitpoint *hp)
{
	t_ray		light;
	t_hitpoint	eclipse;
	float		distance_to_light;
	float		dot;

	light = ray_to_light(hp->pos, data->light.pos);
	distance_to_light = vec3_distance(hp->pos, data->light.pos);
	eclipse = hit_hitable(data->hitables, light);
	if (eclipse.hit == 1 && eclipse.distance > 0
		&& eclipse.distance < distance_to_light)
		return (0);
	dot = vec3_dot(light.dir, vec3_unit(hp->surface_normal_of_hittable));
	if (dot < 0)
		dot = 0;
	return (dot * data->light.brightness);
}

int	color_add_light(t_hitpoint *hp, t_data *data)
{
	int		c;
	float	scale;
	
	scale = get_diffuse_scale(data, hp);
	if (scale < data->ambient.brightness)
		scale = data->ambient.brightness;
	c = scale_color(hp->color, scale);
	return (c);
}