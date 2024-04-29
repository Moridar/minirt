/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit_getcolor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:37:40 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/29 10:42:22 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	getcolor_sphere(t_hitable *obj, t_hitpoint *hp)
{
	float	u;
	float	v;
	int		x;
	int		y;

	if (obj->checker_size <= 0)
		return (obj->color);
	u = atan2(hp->normal.z, hp->normal.x) / (2.0 * M_PI) * obj->diameter;
	v = asin(hp->normal.y) / M_PI * obj->diameter;
	x = u / obj->checker_size;
	y = v / obj->checker_size;
	if (u < 0)
		x++;
	if (v < 0)
		y++;
	if ((x + y) % 2 == 0)
		return (obj->color1);
	return (obj->color);
}

int	getcolor_plane(t_hitable *obj, t_hitpoint *hp)
{
	float		u;
	float		v;
	int			x;
	int			y;
	t_vector3	e;

	if (obj->checker_size <= 0)
		return (obj->color);
	e = vec3_unit(vec3_cross(obj->normal, (t_vector3){1, 0, 0}));
	if (vec3_length(e) < 0.01)
		e = vec3_unit(vec3_cross(obj->normal, (t_vector3){0, 0, 1}));
	u = vec3_dot(hp->pos, e);
	e = vec3_unit(vec3_cross(obj->normal, e));
	v = vec3_dot(hp->pos, e);
	x = u / obj->checker_size;
	y = v / obj->checker_size;
	if (u < 0)
		x++;
	if (v < 0)
		y++;
	if ((x + y) % 2 == 0)
		return (obj->color1);
	return (obj->color);
}

int	getcolor_cylinder(t_hitable *obj, t_hitpoint *hp)
{
	float		angle;
	float		u;
	float		v;
	int			x;
	int			y;

	// if its the top or bottom
	if (obj->checker_size <= 0)
		return (obj->color);
	// the atan is not right, it presumes that we have a diff in z 
	// this has to factor if its tilted so cone needs some other multiply
	// it gives between 1 and -1 and acos why is it -46.. do we need to unit the cross? 
	angle = vec3_dot(vec3_unit(vec3_cross(vec3_scale(obj->normal, -1), (t_vector3){1, 0, 0})), hp->normal);
	// this is const for cyl, but still makes is more dependent on the ratio
	u = acos(angle) * obj->diameter; // that is the cylinder no?
	if (obj->color1 == 0xFFFFFFFF)
		printf("u: %f, angle : %f\n", u, angle);
	v = vec3_dot(vec3_sub(hp->pos, obj->pos), obj->normal) / (1 - vec3_dot(hp->normal, obj->normal));
	x = u / obj->checker_size;
	y = v / obj->checker_size;
	// if (x <= 0)
	// 	x++;
	if ((y+x) % 2 == 0)
		return (obj->color1);
	return (obj->color);
	// where do we take the angle?
}
