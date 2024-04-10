/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:50:15 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/10 15:18:38 by dhorvath         ###   ########.fr       */
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
	hp.distance = d;
	return (hp);
}

t_hitpoint	hit_cylinder(t_hitable cylinder, t_ray ray)
{
	t_hitpoint	hp;
	float		d;
	float		mind;

	// hit caps
	d = 0;
	hp.hit = 0;
	mind = 214743647;
	
	t_vector3 center = vec3_add(cylinder.pos, vec3_scale(cylinder.normal, cylinder.height / 2));
	d = vec3_dot(center, center) / vec3_dot(center, ray.dir);
	if (vec3_length(vec3_scale(ray.dir, d)) < cylinder.diameter / 2.0f)
	{
		hp.hit = 1;
		hp.color = cylinder.color;
		hp.surface_normal_of_hittable = cylinder.normal;
		hp.distance = d;
		mind = d;
	}

	center = vec3_add(cylinder.pos, vec3_scale(cylinder.normal, cylinder.height / -2));
	d = vec3_dot(center, center) / vec3_dot(center, ray.dir);
	if (vec3_length(vec3_scale(ray.dir, d)) < cylinder.diameter / 2.0f && mind > d)
	{
		hp.hit = 1;
		hp.color = cylinder.color;
		hp.surface_normal_of_hittable = vec3_scale(cylinder.normal, -1);
		hp.distance = d;
		mind = d;
	}
	// side
	// calc line facing normal
	t_vector3 b = vec3_sub(cylinder.pos, *ray.origin);
	float disc = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(ray.dir, cylinder.normal)) * pow(cylinder.diameter / 2, 2) - pow(vec3_dot(b, vec3_cross(ray.dir, cylinder.normal)), 2); 
	if (disc >= 0)
	{
		d = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(b, cylinder.normal)) + sqrt(disc);
		float t = vec3_dot(vec3_sub(vec3_add(vec3_scale(ray.dir, d), *ray.origin), cylinder.pos), cylinder.normal);
		if (t <= cylinder.height / 2 && t >= cylinder.height / -2)
		{
			if (mind > d)
			{
				hp.hit = 1;
				hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
				hp.color = cylinder.color;
				hp.surface_normal_of_hittable = vec3_unit(vec3_sub(vec3_sub(vec3_scale(ray.dir, d), vec3_scale(cylinder.normal, t)), b));
				mind = d;
				hp.distance = d;
			}
		}
		d = vec3_dot(vec3_cross(ray.dir, cylinder.normal), vec3_cross(b, cylinder.normal)) - sqrt(disc);
		if (mind > d)
		{
			t = vec3_dot(vec3_sub(vec3_add(vec3_scale(ray.dir, d), *ray.origin), cylinder.pos), cylinder.normal);
			if (t <= cylinder.height / 2 && t >= cylinder.height / -2)
			{
				hp.hit = 1;
				hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, d));
				hp.color = cylinder.color;
				hp.surface_normal_of_hittable = vec3_unit(vec3_sub(vec3_sub(vec3_scale(ray.dir, d), vec3_scale(cylinder.normal, t)), b));
				hp.distance = d;
			}
		}
	}
	return (hp);
}

t_hitpoint	hit_sphere(t_hitable sphere, t_ray ray)
{
	t_discrimininant	dis;
	t_hitpoint			hp;

	hp.hit = 0;
	dis.oc = vec3_sub(*ray.origin, sphere.pos);
	dis.a = vec3_dot(ray.dir, ray.dir);
	dis.b = 2.0 * vec3_dot(dis.oc, ray.dir);
	dis.c = vec3_dot(dis.oc, dis.oc) - sphere.diameter * sphere.diameter;
	dis.discriminant = dis.b * dis.b - 4 * dis.a * dis.c;
	if (dis.discriminant < 0)
		return (hp);
	hp.hit = 1;
	hp.distance = (-dis.b - sqrt(dis.discriminant)) / (2 * dis.a);
	hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, hp.distance));
	hp.color = sphere.color;
	hp.surface_normal_of_hittable = vec3_unit(vec3_sub(hp.pos, sphere.pos));
	return (hp);
}

t_hitpoint	hit_hitable(t_hitable *list, t_ray ray)
{
	t_hitable	*tmp;
	t_hitpoint	hp;
	t_hitpoint	tmp_hp;

	hp.hit = 0;
	tmp = list;
	while (tmp)
	{
		tmp_hp.hit = 0;
		if (tmp->type == 's')
			tmp_hp = hit_sphere(*tmp, ray);
		if (tmp->type == 'c')
			tmp_hp = hit_cylinder(*tmp, ray);
		if (tmp->type == 'p')
			tmp_hp = hit_plane(*tmp, ray);
		if (tmp_hp.hit && (!hp.hit || tmp_hp.distance < hp.distance))
			hp = tmp_hp;
		tmp = tmp->next;
	}
	return (hp);
}
