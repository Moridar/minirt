/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:07:34 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/08 14:53:18 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int is_intersecting_sphere(t_sphere s, t_ray ray)
{
	if (pow(s.center.x * ray.dir.x + s.center.y * ray.dir.y + s.center.z * ray.dir.z, 2)
		- (pow(s.center.x, 2) + pow(s.center.y, 2) + pow(s.center.z, 2)) + pow(s.radius, 2) >= 0)
		return (1);
	return (0);

}