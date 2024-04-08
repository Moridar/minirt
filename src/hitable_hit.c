/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:50:15 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/08 18:04:56 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpoint	hit_plane(t_hitable plane, t_ray ray)
{
	t_hitpoint	hp;
	float		d;

	hp.hit = 0;
	if (vec3_dot(plane.normal, ray.dir) == 0
		|| vec3_dot(vec3_sub(plane.pos, *ray.origin), plane.normal) == 0)
		return (hp);
	d = vec3_dot(vec3_sub(plane.pos, *ray.origin), plane.normal)
		/ vec3_dot(ray.dir, plane.normal);
	hp.hit = 1;
	hp.surface_normal_of_hittable = plane.normal;
	hp.color = plane.color;
	hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
	return (hp);
}

t_hitpoint	hit_cylinder(t_hitable cylinder, t_ray ray)
{
	t_hitpoint	hp;
	t_hitpoint	partial;
	float		d;

	// hit caps
	partial = hit_plane((t_hitable){'p', vec3_add(cylinder.pos,
				vec3_scale(cylinder.normal, cylinder.height / 2)),
			{0, 0, 0}, 0, 0, 0, NULL}, ray);
	if (partial.hit && vec3_length(vec3_sub(partial.pos, vec3_add(cylinder.pos,
					vec3_scale(cylinder.normal, cylinder.height / 2))))
		< cylinder.diameter / 2)
	{
		hp.hit = 1;
		hp.pos = partial.pos;
		hp.color = cylinder.color;
		hp.surface_normal_of_hittable = cylinder.normal;
	}
	// other cap
	partial = hit_plane((t_hitable){'p', vec3_add(cylinder.pos,
				vec3_scale(cylinder.normal, -1 * cylinder.height / 2)),
			{0, 0, 0}, 0, 0, 0, NULL}, ray);
	if (partial.hit && vec3_length(vec3_sub(partial.pos, vec3_add(cylinder.pos,
					vec3_scale(cylinder.normal, cylinder.height / 2))))
		< cylinder.diameter / 2)
	{
		if (vec3_length(vec3_sub(*ray.origin, hp.pos))
			> vec3_length(vec3_sub(*ray.origin, partial.pos)))
		{
			hp.hit = 1;
			hp.pos = partial.pos;
			hp.color = cylinder.color;
			hp.surface_normal_of_hittable = cylinder.normal;
		}
	}
	else
	{
		if (vec3_length(vec3_sub(partial.pos, vec3_add(cylinder.pos,
						vec3_scale(cylinder.normal, cylinder.height / 2))))
			< cylinder.diameter / 2)
		{
			hp.hit = 1;
			hp.pos = partial.pos;
			hp.color = cylinder.color;
			hp.surface_normal_of_hittable = cylinder.normal;
		}
	}
	// side
	// calc line facing normal
	t_vector3 b = vec3_sub(vec3_add(cylinder.pos, vec3_scale(cylinder.normal, -1 * cylinder.height / 2)), *ray.origin);
	float disc = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(ray.dir, cylinder.normal)) * pow(cylinder.diameter / 2, 2) - pow(vec3_dot(b, vec3_cross(ray.dir, cylinder.normal)), 2); 
	if (disc >= 0)
	{
		d = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(b, cylinder.normal)) + sqrt(disc);
		float t = vec3_dot(vec3_sub(vec3_scale(ray.dir, d), b), cylinder.normal);
		if (t < cylinder.height && t > 0)
		{
			if (hp.hit)
			{
				if (d < vec3_length(vec3_sub(*ray.origin, hp.pos)))
				{
					hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
					hp.surface_normal_of_hittable = (t_vector3){0,0,1};
				}
			}
			else
			{
				hp.hit = 1;
				hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
				hp.surface_normal_of_hittable = (t_vector3){0,0,1};
			}
		}
	}
	return (hp);
}

t_hitpoint hit_sphere(t_hitable sphere, t_ray ray)
{
	t_vector3	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_hitpoint	hp;
	float		distance;
	// float		temp;

	hp.hit = 0;
	oc = vec3_sub(*ray.origin, sphere.pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sphere.diameter * sphere.diameter;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hp);
	else
	{
		hp.hit = 1;
		distance = (-b + sqrt(discriminant)) / (2 * a);
		hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, distance));
		hp.color = sphere.color;
		hp.surface_normal_of_hittable = vec3_unit(vec3_sub(hp.pos, sphere.pos));
	}
	return (hp);
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
			if (hit_sphere(*tmp, ray).hit)
				return (tmp->color);
		}
		tmp = tmp->next;
	}
	return (0);
}
