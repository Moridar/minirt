/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:03:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/22 15:42:37 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	create_ray(t_vector3 to, t_vector3 *from)
{
	t_ray	light;

	light.dir = vec3_unit(vec3_sub(to, *from));
	light.origin = from;
	// printf("light orign: %f %f %f\n", light.origin->x, light.origin->y, light.origin->z);

	return (light);
}
static int get_diffuse_color(t_data *data, t_hitpoint *hp)
{
	float		dot;
	t_vector3 lightInDir;
	
	lightInDir = vec3_unit(vec3_sub(data->light.pos, hp->pos));
	dot = vec3_dot(lightInDir, hp->surface_normal_of_hittable);
	return (scale_color(data->light.color, dot));
}
static int get_specular_color(t_data *data, t_hitpoint *hp)
{
	t_vector3 viewDir;
	t_vector3 reflectDir;
	t_vector3 lightInDir;
	float		spec;
	float		dot;
	
	lightInDir = vec3_unit(vec3_sub(data->light.pos, hp->pos));
	viewDir = vec3_unit(vec3_sub(hp->pos, data->camera.pos));
	dot = vec3_dot(lightInDir, hp->surface_normal_of_hittable);
	reflectDir = vec3_unit(vec3_sub(lightInDir, vec3_scale(hp->surface_normal_of_hittable, 2.0f * dot)));
	spec = pow(fmax(vec3_dot(viewDir, reflectDir), 0.0), 32);
	return (scale_color(data->light.color, spec * data->light.brightness));
}

static int check_eclipse(t_hitpoint *hp, t_data *data)
{
	t_ray light;
	t_hitpoint eclipse;
	float distance_to_light;

	light = create_ray(hp->pos, &data->light.pos);
	distance_to_light = vec3_distance(hp->pos, data->light.pos);
	eclipse = hit_hitable(data->hitables, light);
	if (eclipse.hit && eclipse.distance + 0.01 < distance_to_light)
		return (1);
	return (0);
}

int	color_add_light(t_hitpoint *hp, t_data *data)
{
	unsigned int		c;
	int		diffuse;
	int		specular;
	int		ambient;
	
	ambient = scale_color(data->ambient.color, data->ambient.brightness);
	if (check_eclipse(hp, data))
		return (color_multiply(ambient, hp->color));
	diffuse = get_diffuse_color(data, hp);
	specular = get_specular_color(data, hp);
	c = color_multiply(color_add(ambient, diffuse, specular), hp->color);
	// printf("color: %d, %d, %d\n", c >> 24, (c >> 16) % 256, (c >> 8) % 256);
	return (c);
}
