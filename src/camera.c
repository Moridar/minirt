/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/07 23:30:05 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(*ray->origin, vec3_scale(ray->dir, t)));
}

t_ray	*create_rays(t_data *data, float distance)
{
	t_ray	*rays;
	int		x;
	int		y;

	rays = ft_calloc(data->width * data->height, sizeof(t_ray));
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			rays[y * data->width + x].dir = (t_vector3){x - data->width / 2.0f,
				y - data->height / 2.0f, distance};
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

	camera.pos = pos;
	camera.normal = normal;
	camera.degree = FOV;
	camera.rays = create_rays(data, 100.0f);
	return (camera);
}
