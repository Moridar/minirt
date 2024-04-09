/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:50:15 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/09 14:25:45 by dhorvath         ###   ########.fr       */
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
	t_hitpoint	partialTop;
	t_hitpoint	partialBot;
	t_hitpoint	partialSide;
	float		d;

	// hit caps
	d = 0;
	hp.hit = 0;
	partialSide.hit = 0;
	partialTop = hit_plane((t_hitable){'p', vec3_add(cylinder.pos,
				vec3_scale(cylinder.normal, cylinder.height / 2)),
			cylinder.normal, 0, 0, 0, NULL}, ray);
	if (partialTop.hit && vec3_length(vec3_sub(partialTop.pos, vec3_add(cylinder.pos,
					vec3_scale(cylinder.normal, cylinder.height / 2))))
		< cylinder.diameter / 2)
	{
		hp.hit = 1;
		hp.pos = partialTop.pos;
		hp.color = cylinder.color;
		hp.surface_normal_of_hittable = cylinder.normal;
	}
	// other cap
	partialBot = hit_plane((t_hitable){'p', vec3_add(cylinder.pos,
				vec3_scale(cylinder.normal, -1 * cylinder.height / 2)),
			vec3_scale(cylinder.normal, -1), 0, 0, 0, NULL}, ray);
	if (partialBot.hit && vec3_length(vec3_sub(partialBot.pos, vec3_add(cylinder.pos,
					vec3_scale(cylinder.normal, cylinder.height / -2))))
		< cylinder.diameter / 2)
	{
		hp.hit = 1;
		hp.pos = partialBot.pos;
		hp.color = cylinder.color;
		hp.surface_normal_of_hittable = cylinder.normal;
	}
	
	// side
	// calc line facing normal
	t_vector3 b = vec3_sub(cylinder.pos, *ray.origin);
	float disc = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(ray.dir, cylinder.normal)) * pow(cylinder.diameter / 2, 2) - pow(vec3_dot(b, vec3_cross(ray.dir, cylinder.normal)), 2); 
	if (disc >= 0)
	{
		d = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(b, cylinder.normal)) + sqrt(disc);
		float t = vec3_dot(vec3_sub(vec3_add(vec3_scale(ray.dir, d), *ray.origin), cylinder.pos), cylinder.normal);
		if (t < cylinder.height / 2 && t > cylinder.height / -2)
		{
			partialSide.hit = 1;
			partialSide.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
			partialSide.surface_normal_of_hittable = (t_vector3){0, 0, 1};
		}
		d = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(b, cylinder.normal)) - sqrt(disc);
		t = vec3_dot(vec3_sub(vec3_add(vec3_scale(ray.dir, d), *ray.origin), cylinder.pos), cylinder.normal);
		if (t < cylinder.height / 2 && t > cylinder.height / -2)
		{
			partialSide.hit = 1;
			partialSide.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
			partialSide.surface_normal_of_hittable = (t_vector3){0, 0, 1};
		}
	}
	if (partialSide.hit)
		return (partialSide);
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

float	ray_to_light(t_vector3* pos, t_vector3 lightpos, t_vector3 normal, t_vector3 inray)
{
	t_ray	light;
	float	dot;
	float	dotcam;

	light.dir = vec3_unit(vec3_sub(lightpos, *pos));
	light.origin = pos;
	dot = vec3_dot(light.dir, normal);
	dotcam = vec3_dot(inray, normal);
	return ((acos(dot) - acos(dotcam) + 3.14) / 6.28);
}

unsigned int scale_color(unsigned int col, float scale)
{
	return ((col / 256) * scale * 256 + 255);
}

int	hit_hitable(t_hitable *list, t_ray ray)
{
	t_hitable	*tmp;
	t_hitpoint	hp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == 's')
		{
			hp = hit_sphere(*tmp, ray);
			if (hp.hit)
				return (scale_color(tmp->color, ray_to_light(&hp.pos, (t_vector3){0,0,0}, hp.surface_normal_of_hittable, ray.dir)));
				//return (((int)(hp.surface_normal_of_hittable.x * 255) << 24) + (hp.surface_normal_of_hittable.y << 16) + (hp.surface_normal_of_hittable.z << 8) + 255;)
		}
		if (tmp->type == 'c')
		{
			if (hit_cylinder(*tmp, ray).hit)
				return (tmp->color);
		}
		if (tmp->type == 'p')
		{
			if (hit_plane(*tmp, ray).hit)
				return (tmp->color);
		}
		tmp = tmp->next;
	}
	return (0);
}
