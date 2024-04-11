/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:03:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/11 16:01:35 by bsyvasal         ###   ########.fr       */
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
static int get_diffuse_color(t_data *data, t_hitpoint *hp)
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
	return (scale_color(data->light.color, dot));
}
static int get_specular_color(t_data *data, t_hitpoint *hp)
{
	t_vector3 viewDir;
	t_vector3 reflectDir;
	t_vector3 lightDir;
	float		spec;

	lightDir = vec3_unit(vec3_sub(data->light.pos, hp->pos));
	viewDir = vec3_unit(vec3_sub(data->camera.pos, hp->pos));
	reflectDir = vec3_reflect(lightDir, hp->surface_normal_of_hittable);
	spec = pow(fmax(vec3_dot(viewDir, reflectDir), 0.0), 32);
	return (scale_color(data->light.color, spec * data->light.brightness));
}

int	color_add_light(t_hitpoint *hp, t_data *data)
{
	int		c;
	int		diffuse;
	int		specular;
	int		ambient;
	
	ambient = scale_color(data->ambient.color, data->ambient.brightness);
	diffuse = get_diffuse_color(data, hp);
	specular = get_specular_color(data, hp);
	specular = 0;
	c = color_multiply(color_add(ambient, diffuse, specular), hp->color);
	return (c);
}