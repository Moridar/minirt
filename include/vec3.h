/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:13:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/22 11:20:27 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

t_vector3	vec3_add(t_vector3 a, t_vector3 b);
t_vector3	vec3_sub(t_vector3 a, t_vector3 b);
t_vector3	vec3_mul(t_vector3 a, t_vector3 b);
t_vector3	vec3_div(t_vector3 a, t_vector3 b);
t_vector3	vec3_scale(t_vector3 a, float scale);
t_vector3	vec3_cross(t_vector3 a, t_vector3 b);
float		vec3_dot(t_vector3 a, t_vector3 b);
float		vec3_length(t_vector3 a);
t_vector3	vec3_unit(t_vector3 a);
float		vec3_distance(t_vector3 pos_a, t_vector3 pos_b);

#endif