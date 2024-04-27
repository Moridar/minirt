/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/27 03:00:49 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector3	vec3_rotate(t_vector3 vec, t_vecrotation *rv)
{
	t_vector3	rotated_vec;

	rotated_vec.x = (rv->cos + rv->invcos * rv->axis.x * rv->axis.x) * vec.x
		+ (rv->invcos * rv->axis.x * rv->axis.y - rv->sin * rv->axis.z) * vec.y
		+ (rv->invcos * rv->axis.x * rv->axis.z + rv->sin * rv->axis.y) * vec.z;
	rotated_vec.y
		= (rv->invcos * rv->axis.x * rv->axis.y + rv->sin * rv->axis.z) * vec.x
		+ (rv->cos + rv->invcos * rv->axis.y * rv->axis.y) * vec.y
		+ (rv->invcos * rv->axis.y * rv->axis.z - rv->sin * rv->axis.x) * vec.z;
	rotated_vec.z
		= (rv->invcos * rv->axis.x * rv->axis.z - rv->sin * rv->axis.y) * vec.x
		+ (rv->invcos * rv->axis.y * rv->axis.z + rv->sin * rv->axis.x) * vec.y
		+ (rv->cos + rv->invcos * rv->axis.z * rv->axis.z) * vec.z;
	return (rotated_vec);
}

t_ray	create_ray(t_data *data, int x, int y)
{
	t_vector3		vec;
	t_ray			ray;

	vec.z = data->raycfg.vecz;
	vec.x = x - (int) data->img->width / 2;
	vec.y = (int) data->img->height / 2 - y;
	if (data->camera.normal.z < 0)
		vec.y *= -1;
	vec = vec3_rotate(vec, &data->raycfg.yaw);
	vec = vec3_rotate(vec, &data->raycfg.pitch);
	ray.origin = &data->camera.pos;
	ray.dir = vec3_unit(vec);
	return (ray);
}

void	create_camera(t_data *data, t_vector3 pos,
				t_vector3 normal, int FOV)
{
	ft_printf("camera created\n");
	data->camera.pos = pos;
	data->camera.normal = vec3_unit(normal);
	data->camera.degree = FOV;
}
