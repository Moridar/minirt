/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:31:13 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/25 17:50:27 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_discrimininant	discriminant(t_hitable cone, t_ray ray, float angle)
{
	t_discrimininant	dis;

	dis.oc = vec3_sub(*ray.origin, cone.pos);
	dis.a = 1 - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(ray.dir, cone.normal), 2);
	dis.b = 2 * (vec3_dot(ray.dir, dis.oc) - (1 + pow(tan(angle), 2))
			* vec3_dot(ray.dir, cone.normal) * vec3_dot(dis.oc, cone.normal));
	dis.c = vec3_dot(dis.oc, dis.oc) - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(dis.oc, cone.normal), 2);
	dis.discriminant = dis.b * dis.b - 4 * dis.a * dis.c;
	return (dis);
}

int	calc_vertex_normal(t_hitable cone, t_ray ray, t_hitpoint *hp, float angle)
{
	float				height;
	t_vector3			hit_to_vertex;
	t_vector3			projection;
	t_vector3			normal;

	if (hp->distance < 0)
		return (0);
	hp->pos = vec3_add(*ray.origin, vec3_scale(ray.dir, hp->distance));
	height = vec3_dot(vec3_sub(hp->pos, cone.pos), cone.normal);
	if (height < 0 || height > cone.height)
		return (0);
	hit_to_vertex = vec3_sub(hp->pos, cone.pos);
	projection = vec3_scale(cone.normal, vec3_dot(hit_to_vertex, cone.normal)
			/ vec3_dot(cone.normal, cone.normal));
	normal = vec3_unit(vec3_sub(hit_to_vertex, projection));
	hp->surface_normal_of_hittable
		= vec3_unit(vec3_sub(normal, vec3_scale(cone.normal, tan(angle))));
	return (1);
}

t_hitpoint	hit_cone(t_hitable cone, t_ray ray)
{
	t_hitpoint			hpa;
	t_hitpoint			hpb;
	t_discrimininant	dis;
	float				angle;

	hpa.hit = 0;
	hpb.hit = 0;
	angle = atan((cone.diameter / 2) / cone.height);
	dis = discriminant(cone, ray, angle);
	if (dis.discriminant < 0.00)
		return (hpa);
	hpa.distance = (-dis.b - sqrt(dis.discriminant)) / (2 * dis.a);
	hpb.distance = (-dis.b + sqrt(dis.discriminant)) / (2 * dis.a);
	hpa.hit = calc_vertex_normal(cone, ray, &hpa, angle);
	hpb.hit = calc_vertex_normal(cone, ray, &hpb, angle);
	if (hpa.hit == 0 && hpb.hit == 0)
		return (hpa);
	if (hpb.hit)
		hpb.surface_normal_of_hittable
			= vec3_scale(hpb.surface_normal_of_hittable, -1.0f);
	hpa.color = cone.color;
	hpb.color = scale_color(cone.color, 0.87);
	if (hpa.hit == 0 || (hpb.hit && hpa.distance > hpb.distance))
		hpa = hpb;
	return (hpa);
}

t_hitpoint	hit_circle(t_hitable plane, t_ray ray, float radius)
{
	t_hitpoint		hp;

	hp = hit_plane(plane, ray);
	hp.color = scale_color(hp.color, 0.7);
	if (hp.hit && vec3_distance(hp.pos, plane.pos) <= radius)
		return (hp);
	hp.hit = 0;
	return (hp);
}
