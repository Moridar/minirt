/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/12 12:59:49 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

t_vector3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(*ray->origin, vec3_scale(ray->dir, t)));
}

t_ray	*create_rays(t_data *data, float FOV)
{
	t_ray		*rays;
	int			x;
	int			y;
	float		dist;
	t_vector3	vec;

	rays = ft_calloc(data->width * data->height, sizeof(t_ray));
	dist = (data->width / 2) / tan(FOV / 360 * M_PI);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			vec.x = x - data->width / 2;
			vec.y = 0 - (y - data->height / 2);
			vec.z = dist;
			vec = vec3_unit(vec);
			rays[y * data->width + x].dir = 
					vec3_unit(vec3_add(vec, data->camera.normal));
			rays[y * data->width + x].origin = &data->camera.pos;
		}
	}
	printf("rays created\n");
	return (rays);
}

void	create_camera(t_data *data, t_vector3 pos,
				t_vector3 normal, int FOV)
{
	ft_printf("camera created\n");
	data->camera.pos = pos;
	data->camera.normal = vec3_unit(normal);
	data->camera.degree = FOV;
	data->camera.rays = create_rays(data, FOV);
}
