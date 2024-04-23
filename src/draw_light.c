/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:03:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/23 22:42:56 by bsyvasal         ###   ########.fr       */
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
static int get_diffuse_color(t_hitpoint *hp, t_light *target)
{
	float		dot;
	t_vector3 lightInDir;
	
	lightInDir = vec3_unit(vec3_sub(target->pos, hp->pos));
	dot = vec3_dot(lightInDir, hp->surface_normal_of_hittable);
	return (scale_color(target->color, dot));
}
static int get_specular_color(t_data *data, t_hitpoint *hp, t_light *target)
{
	t_vector3 viewDir;
	t_vector3 reflectDir;
	t_vector3 lightInDir;
	float		spec;
	float		dot;
	
	lightInDir = vec3_unit(vec3_sub(target->pos, hp->pos));
	viewDir = vec3_unit(vec3_sub(hp->pos, data->camera.pos));
	dot = vec3_dot(lightInDir, hp->surface_normal_of_hittable);
	reflectDir = vec3_unit(vec3_sub(lightInDir, vec3_scale(hp->surface_normal_of_hittable, 2.0f * dot)));
	spec = pow(fmax(vec3_dot(viewDir, reflectDir), 0.0), 32);
	return (scale_color(target->color, spec * target->brightness));
}

static int check_eclipse(t_hitpoint *hp, t_data *data, t_light *target)
{
	t_ray light;
	t_hitpoint eclipse;
	float distance_to_light;

	light = create_ray(hp->pos, &target->pos);
	distance_to_light = vec3_distance(hp->pos, target->pos);
	eclipse = hit_hitable(data->hitables, light);
	if (eclipse.hit && eclipse.distance + 0.01 < distance_to_light)
		return (1);
	return (0);
}

int	color_add_light(t_hitpoint *hp, t_data *data)
{
	unsigned int	c;
	int				diffuse;
	int				specular;
	int				ambient;
	t_light			*current;
	
	ambient = scale_color(data->ambient.color, data->ambient.brightness);
	current = data->light;
	c = ambient;
	while (current)
	{
		if (!check_eclipse(hp, data, current))
		{
			diffuse = get_diffuse_color(hp, current);
			specular = get_specular_color(data, hp, current);
			c = color_add(c, diffuse, specular);
		}
		current = current->next;
	}
	c = color_multiply(hp->color, c);
	// printf("color: %d, %d, %d\n", c >> 24, (c >> 16) % 256, (c >> 8) % 256);
	return (c);
}
