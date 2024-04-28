/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:50:15 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/28 15:41:03 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpoint	hit_plane(t_hitable plane, t_ray ray)
{
	t_hitpoint	hp;

	hp.hit = 0;
	if (vec3_dot(plane.normal, ray.dir) == 0
		|| vec3_dot(vec3_unit(vec3_sub(plane.pos, *ray.origin)),
			plane.normal) == 0)
		return (hp);
	if (vec3_dot(ray.dir, plane.normal) > 0)
		plane.normal = vec3_scale(plane.normal, -1);
	hp.distance = vec3_dot(vec3_sub(plane.pos, *ray.origin), plane.normal)
		/ vec3_dot(ray.dir, plane.normal);
	if (hp.distance <= 0)
		return (hp);
	hp.hit = 1;
	hp.normal = plane.normal;
	hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, hp.distance));
	hp.color = getcolor_plane(&plane, &hp);
	return (hp);
}

static t_hitpoint	hit_cylinder_side(t_hitable cyl, t_ray ray)
{
	t_hitpoint		hp;
	t_hitpoint		hpb;
	const t_vector3	cross = vec3_cross(ray.dir, cyl.normal);
	const t_vector3	crossbcnormal = vec3_cross(vec3_sub(cyl.pos,
				*ray.origin), cyl.normal);
	const float		disc = vec3_dot(cross, cross) * pow(cyl.diameter / 2,
			2) - pow(vec3_dot(vec3_sub(cyl.pos, *ray.origin), cross), 2);

	hp.hit = 0;
	if (disc < 0)
		return (hp);
	hp.distance = (vec3_dot(cross, crossbcnormal) - sqrt(disc))
		/ vec3_dot(cross, cross);
	hp.hit = calc_vertex_normal(cyl, ray, &hp, 0);
	hpb.distance = (vec3_dot(cross, crossbcnormal) + sqrt(disc))
		/ vec3_dot(cross, cross);
	hpb.hit = calc_vertex_normal(cyl, ray, &hpb, 0);
	if (hpb.hit && (hpb.distance < hp.distance || !hp.hit))
		return (hpb);
	return (hp);
}

static t_hitpoint	hit_cylinder(t_hitable cyl, t_ray ray)
{
	t_hitpoint	hit_side;
	t_hitpoint	hit_cap1;
	t_hitpoint	hit_cap2;
	t_hitpoint	hp;

	hit_side = hit_cylinder_side(cyl, ray);
	hit_cap2 = hit_circle((t_hitable){'p', cyl.pos, cyl.normal, 1, 1,
			cyl.color, 0, 0, NULL}, ray, cyl.diameter / 2);
	hit_cap1 = hit_circle((t_hitable){'p', vec3_add(cyl.pos,
				vec3_scale(cyl.normal, cyl.height)), cyl.normal, 1, 1,
			cyl.color, 0, 0, NULL}, ray, cyl.diameter / 2);
	hp = hit_side;
	if (hit_cap1.hit && (!hp.hit || hp.distance > hit_cap1.distance))
		hp = hit_cap1;
	if (hit_cap2.hit && (!hp.hit || hp.distance > hit_cap2.distance))
		hp = hit_cap2;
	hp.color = getcolor_plane(&cyl, &hp);
	return (hp);
}

static t_hitpoint	hit_sphere(t_hitable sph, t_ray ray)
{
	t_discrimininant	dis;
	t_hitpoint			hp;

	hp.hit = 0;
	dis.oc = vec3_sub(*ray.origin, sph.pos);
	dis.a = vec3_dot(ray.dir, ray.dir);
	dis.b = 2.0 * vec3_dot(dis.oc, ray.dir);
	dis.c = vec3_dot(dis.oc, dis.oc) - sph.diameter / 2 * sph.diameter / 2;
	dis.discriminant = dis.b * dis.b - 4 * dis.a * dis.c;
	if (dis.discriminant < 0)
		return (hp);
	hp.distance = (-dis.b - sqrt(dis.discriminant)) / (2 * dis.a);
	if (hp.distance <= 0.00001)
		hp.distance = (-dis.b + sqrt(dis.discriminant)) / (2 * dis.a);
	if (hp.distance <= 0.00001)
		return (hp);
	hp.hit = 1;
	hp.pos = vec3_add(*ray.origin, vec3_scale(ray.dir, hp.distance));
	hp.normal = vec3_unit(vec3_sub(hp.pos, sph.pos));
	if (vec3_dot(ray.dir, hp.normal) > 0)
		hp.normal = vec3_scale(hp.normal, -1);
	hp.color = getcolor_sphere(&sph, &hp);
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
		if (tmp->type == 'o')
			tmp_hp = hit_cone(*tmp, ray);
		if (tmp_hp.hit && tmp_hp.distance > 0
			&& (!hp.hit || tmp_hp.distance < hp.distance))
			hp = tmp_hp;
		tmp = tmp->next;
	}
	return (hp);
}
