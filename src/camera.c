/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:53:17 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/04 19:56:50 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

typedef struct s_vector3
{
	float x;
	float y;
	float z;
} t_vector3;


typedef struct s_ray
{
	t_vector3 dir;
} t_ray;

typedef struct s_camera
{
	int width;
	int height;
	float distance;
	t_ray *rays;
}	t_camera;

t_ray *create_rays(int width, int height, float distance)
{
	t_ray *rays;
	int x;
	int y;

	rays = ft_calloc(width * height, sizeof(t_ray));
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			rays[y * width + x].dir = (t_vector3){x - width / 2.0f, y - height / 2.0f, distance};
			printf("%f %f %f\n", x - width / 2.0f, y - height / 2.0f, distance);
			x++;
		}
		y++;
	}
	return (rays);
}

t_camera *create_camera(int width, int height, float distance)
{
	t_camera *cam;

	cam = ft_calloc(1, sizeof(t_camera));
	cam->distance = distance;
	cam->width = width;
	cam->height = height;
	cam->rays = create_rays(width, height, distance);
	return (cam);
}
