/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:03:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/26 18:58:35 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	create_ray(t_vector3 to, t_vector3 *from)
{
	t_ray	light;

	light.dir = vec3_unit(vec3_sub(to, *from));
	light.origin = from;
	return (light);
}

static int	get_diffuse_color(t_hitpoint *hp, t_light *target)
{
	float		dot;
	t_vector3	lightdir;

	lightdir = vec3_unit(vec3_sub(target->pos, hp->pos));
	dot = vec3_dot(lightdir, hp->normal);
	return (color_scale(target->color, dot));
}

static int	get_specular_color(t_data *data, t_hitpoint *hp, t_light *target)
{
	t_vector3	view_dir;
	t_vector3	reflect_dir;
	t_vector3	light_dir;
	float		spec;
	float		dot;

	light_dir = vec3_unit(vec3_sub(target->pos, hp->pos));
	view_dir = vec3_unit(vec3_sub(hp->pos, data->camera.pos));
	dot = vec3_dot(light_dir, hp->normal);
	reflect_dir = vec3_unit(vec3_sub(light_dir,
				vec3_scale(hp->normal, 2.0f * dot)));
	spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);
	return (color_scale(target->color, spec * target->brightness));
}

static int	check_eclipse(t_hitpoint *hp, t_data *data, t_light *target)
{
	t_ray		light;
	t_hitpoint	eclipse;
	float		distance_to_light;

	light = create_ray(hp->pos, &target->pos);
	distance_to_light = vec3_distance(hp->pos, target->pos);
	eclipse = hit_hitable(data->hitables, light);
	if (eclipse.hit && eclipse.distance + 0.01 < distance_to_light)
		return (1);
	return (0);
}

int	color_add_light(t_hitpoint *hp, t_data *data)
{
	unsigned int	total_color;
	int				diffuse;
	int				specular;
	t_light			*lightptr;

	lightptr = data->light;
	total_color = color_scale(data->ambient.color, data->ambient.brightness);
	total_color = color_add(total_color, color_scale(0xFFFFFFFF, 0.1), 0);
	while (lightptr)
	{
		if (!check_eclipse(hp, data, lightptr))
		{
			diffuse = get_diffuse_color(hp, lightptr);
			specular = get_specular_color(data, hp, lightptr);
			total_color = color_add(total_color, diffuse, specular);
		}
		lightptr = lightptr->next;
	}
	total_color = color_multiply(hp->color, total_color);
	return (total_color);
}
