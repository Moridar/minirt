/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/26 16:17:17 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

static t_vector3	vec3_rotate(t_vector3 vec, t_rotate_vector *rv)
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

void	rv_setdata(t_data *data, t_rotate_vector *yaw, t_rotate_vector *pitch)
{
	t_vector3	normal;

	normal = data->camera.normal;
	normal.y = 0;
	normal = vec3_unit(normal);
	yaw->axis = vec3_cross(((t_vector3){0, 0, 1}), normal);
	yaw->cos = vec3_dot((t_vector3){0, 0, 1}, normal);
	yaw->sin = sin(acos(yaw->cos));
	yaw->invcos = 1.0f - yaw->cos;
	pitch->axis = vec3_cross(normal, (t_vector3){0, 1, 0});
	pitch->sin = data->camera.normal.y;
	pitch->cos = cos(asin(pitch->sin));
	pitch->invcos = 1.0f - pitch->cos;
}

void	create_rays(t_data *data, float FOV, t_ray *rays)
{
	int				x;
	int				y;
	t_vector3		vec;
	t_rotate_vector	yaw_rv;
	t_rotate_vector	pitch_rv;

	rv_setdata(data, &yaw_rv, &pitch_rv);
	vec.z = (data->img->width / 2) / tan(FOV * M_PI / 360);
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
				= vec3_unit(vec3_rotate(vec3_rotate(vec, &yaw_rv), &pitch_rv));
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
