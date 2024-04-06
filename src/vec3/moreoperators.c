/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreoperators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:15:48 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 14:26:12 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float	vec3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	vec3_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

float	vec3_length(t_vector3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector3	vec3_unit(t_vector3 a)
{
	return (vec3_scale(a, 1 / vec3_length(a)));
}