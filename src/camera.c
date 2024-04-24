/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/24 23:12:22 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

t_vector3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(*ray->origin, vec3_scale(ray->dir, t)));
}

t_vector3	rotate_vector(t_vector3 vec, t_vector3 axis, float angle)
{
	t_vector3	rotated_vec;
	float		cos_theta;
	float		sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	rotated_vec.x = cos_theta * vec.x
		+ sin_theta * (axis.y * vec.z - axis.z * vec.y);
	rotated_vec.y = cos_theta * vec.y
		+ sin_theta * (axis.z * vec.x - axis.x * vec.z);
	rotated_vec.z = cos_theta * vec.z
		+ sin_theta * (axis.x * vec.y - axis.y * vec.x);
	return (rotated_vec);
}

void	*create_rays(t_data *data, float FOV)
{
	int			x;
	int			y;
	float		dist;
	t_vector3	vec;

	data->camera.rays = ft_calloc(data->width * data->height, sizeof(t_ray));
	dist = (data->width / 2) / tan(FOV * M_PI / 360);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			vec.x = x - data->width / 2;
			vec.y = 0 - (y - data->height / 2);
			vec.z = dist;
			vec = rotate_vector(vec, vec3_cross((t_vector3){0, 0, 1},
						data->camera.normal),
					acos(vec3_dot((t_vector3){0, 0, 1}, data->camera.normal)));
			data->camera.rays[y * data->width + x].dir = vec3_unit(vec);
			data->camera.rays[y * data->width + x].origin = &data->camera.pos;
		}
	}
	printf("rays created\n");
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
