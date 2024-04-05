/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/06 01:34:39 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

t_ray	*create_rays(int width, int height, float distance)
{
	t_ray	*rays;
	int		x;
	int		y;

	rays = ft_calloc(width * height, sizeof(t_ray));
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			rays[y * width + x].dir = (t_vector3){x - width / 2.0f, y - height / 2.0f, distance};
			//printf("%f %f %f\n", x - width / 2.0f, y - height / 2.0f, distance);
			x++;
		}
		y++;
	}
	printf("rays created\n");
	return (rays);
}

t_camera	create_camera(t_data *data, t_vector3 pos, t_vector3 normal, int FOV)
{
	t_camera	camera;

	camera.pos = pos;
	camera.normal = normal;
	camera.degree = FOV;
	camera.rays = create_rays(data->width, data->height, 1.0f);
	return (camera);
}
