/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baseoperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:09:57 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 14:27:32 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vector3	vec3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	vec3_sub(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vec3_mul(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

t_vector3	vec3_div(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

t_vector3	vec3_scale(t_vector3 a, float scale)
{
	t_vector3	result;

	result.x = a.x * scale;
	result.y = a.y * scale;
	result.z = a.z * scale;
	return (result);
}
