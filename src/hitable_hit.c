/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:50:15 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/07 23:03:54 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_sphere(t_hitable sphere, t_ray ray)
{
	t_vector3	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	// float		temp;

	oc = vec3_sub(*ray.origin, sphere.pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sphere.diameter * sphere.diameter;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
	// if (discriminant < 0)
	// 	return (0);
	// temp = (-b - sqrt(discriminant)) / (2.0 * a);
	// if (temp < *t && temp > 0.001)
	// {
	// 	*t = temp;
	// 	return (1);
	// }
	// temp = (-b + sqrt(discriminant)) / (2.0 * a);
	// if (temp < *t && temp > 0.001)
	// {
	// 	*t = temp;
	// 	return (1);
	// }
	// return (0);
}

int	hit_hitable(t_hitable *list, t_ray ray)
{
	t_hitable	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == 's')
		{
			if (hit_sphere(*tmp, ray))
				return (tmp->color);
		}
		tmp = tmp->next;
	}
	return (0);
}
