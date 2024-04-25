/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/25 20:04:13 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

t_vector3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(*ray->origin, vec3_scale(ray->dir, t)));
}

t_vector3	rotate_vector(t_vector3 vec, t_vector3 axis,
		float cos_theta, float sin_theta)
{
	t_vector3	rotated_vec;
	float		one_minus_cos_theta;

	one_minus_cos_theta = 1.0f - cos_theta;
	rotated_vec.x = (cos_theta + one_minus_cos_theta * axis.x * axis.x) * vec.x
		+ (one_minus_cos_theta * axis.x * axis.y - sin_theta * axis.z) * vec.y
		+ (one_minus_cos_theta * axis.x * axis.z + sin_theta * axis.y) * vec.z;
	rotated_vec.y = (one_minus_cos_theta * axis.x * axis.y + sin_theta * axis.z)
		* vec.x + (cos_theta + one_minus_cos_theta * axis.y * axis.y) * vec.y
		+ (one_minus_cos_theta * axis.y * axis.z - sin_theta * axis.x) * vec.z;
	rotated_vec.z = (one_minus_cos_theta * axis.x * axis.z - sin_theta * axis.y)
		* vec.x + (one_minus_cos_theta * axis.y * axis.z + sin_theta * axis.x)
		* vec.y + (cos_theta + one_minus_cos_theta * axis.z * axis.z) * vec.z;
	return (vec3_unit(rotated_vec));
}

void	create_rays(t_data *data, float FOV, t_ray *rays)
{
	int			x;
	int			y;
	t_vector3	vec;
	t_vector3	axis;
	float		cossin_theta[2];

	vec.z = (data->img->width / 2) / tan(FOV * M_PI / 360);
	axis = vec3_cross(((t_vector3){0, 0, 1}), data->camera.normal);
	cossin_theta[0] = vec3_dot((t_vector3){0, 0, 1}, data->camera.normal);
	cossin_theta[1] = sin(acos(cossin_theta[0]));
	y = -1;
	while (++y < (int)data->img->height)
	{
		x = -1;
		while (++x < (int)data->img->width)
		{
			vec.x = x - (int)data->img->width / 2;
			vec.y = (int)data->img->height / 2 - y;
			if (data->camera.normal.z < 0)
				vec.y *= -1;
			rays[y * data->img->width + x].dir
				= rotate_vector(vec, axis, cossin_theta[0], cossin_theta[1]);
			rays[y * data->img->width + x].origin = &data->camera.pos;
		}
	}
}

void	create_camera(t_data *data, t_vector3 pos,
				t_vector3 normal, int FOV)
{
	ft_printf("camera created\n");
	data->camera.pos = pos;
	data->camera.normal = vec3_unit(normal);
	data->camera.degree = FOV;
	data->camera.rays
		= ft_calloc((int)data->img->width * data->img->height, sizeof(t_ray));
	if (!data->camera.rays && destroy(data))
		printf("Fatal: malloc fail\n");
	create_rays(data, FOV, data->camera.rays);
	printf("rays created\n");
}
