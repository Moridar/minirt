/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/09 12:19:47 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

t_vector3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(*ray->origin, vec3_scale(ray->dir, t)));
}

t_ray	*create_rays(t_data *data, float FOV, t_camera camera)
{
	t_ray	*rays;
	int		x;
	int		y;
	float	dist;

	rays = ft_calloc(data->width * data->height, sizeof(t_ray));
  dist = (data->width / 2) / tan(FOV / 360 * 3.14);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			rays[y * data->width + x].dir = vec3_unit(
					vec3_add((t_vector3){x - data->width / 2, y - data->height / 2, dist},
					camera.normal));
			rays[y * data->width + x].origin = &data->camera.pos;
			x++;
		}
		y++;
	}
	printf("rays created\n");
	return (rays);
}

t_camera	create_camera(t_data *data, t_vector3 pos,
				t_vector3 normal, int FOV)
{
	t_camera	camera;

	ft_printf("camera created\n");
	camera.pos = pos;
	camera.normal = normal;
	camera.degree = FOV;
	camera.rays = create_rays(data, FOV, camera);
	return (camera);
}
