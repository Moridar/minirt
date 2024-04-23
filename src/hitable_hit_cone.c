/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:31:13 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/23 14:03:54 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_discrimininant calc_discriminant(t_hitable cone, t_ray ray, float angle)
{
	t_discrimininant	dis;
	
	dis.oc = vec3_sub(*ray.origin, cone.pos);
	dis.a = 1 - (1 + pow(tan(angle), 2)) * pow(vec3_dot(ray.dir, cone.normal), 2);
	dis.b = 2 * (vec3_dot(ray.dir, dis.oc) - (1 + pow(tan(angle), 2)) * vec3_dot(ray.dir, cone.normal) * vec3_dot(dis.oc, cone.normal));
	dis.c = vec3_dot(dis.oc, dis.oc) - (1 + pow(tan(angle), 2)) * pow(vec3_dot(dis.oc, cone.normal), 2);
	dis.discriminant = dis.b * dis.b - 4 * dis.a * dis.c;
	return (dis);
}
int	calc_vertex_normal(t_hitable cone, t_ray ray, t_hitpoint *hp, float angle)
{
	float				height;
	t_vector3			hit_to_vertex;
	
	hp->pos = vec3_add(*ray.origin, vec3_scale(ray.dir, hp->distance));
	height = vec3_dot(vec3_sub(hp->pos, cone.pos), cone.normal);
	hit_to_vertex = vec3_sub(hp->pos, cone.pos);
	hp->surface_normal_of_hittable = vec3_unit(vec3_sub(hit_to_vertex, vec3_scale(cone.normal, vec3_dot(hit_to_vertex, cone.normal) + cone.height * cos(angle))));
	if (hp->distance < 0 || height < 0 || height > cone.height)
		return (0);
	return (1);
}
int is_point_inside_cone(t_vector3 point, t_hitable cone) {
    // Calculate the vector from the cone's vertex to the point
    t_vector3 v = vec3_sub(point, cone.pos);

    // Calculate the dot product of this vector and the cone's direction vector
    float dot = vec3_dot(v, cone.normal);

    // If the dot product is negative, the point is not inside the cone
    if (dot < 0) {
        return 0;
    }

    // Calculate the squared distance from the point to the line along the cone's direction vector
    float dist_sq = vec3_dot(v, v) - dot * dot;

    // Calculate the radius of the cone at the height of the point
    float radius_at_height = (dot / cone.height) * (cone.diameter / 2);

    // If the squared distance is less than the squared radius, the point is inside the cone
    if (dist_sq < radius_at_height * radius_at_height)
        return 1;
    return 0;
}

t_hitpoint	hit_cone(t_hitable cone, t_ray ray)
{
	t_hitpoint			hpa;
	t_hitpoint			hpb;
	t_discrimininant	dis;
	float				angle;
	int					ray_from_inside;

	hpa.hit = 0;
	hpb.hit = 0;
	angle = atan((cone.diameter / 2) / cone.height);
	dis = calc_discriminant(cone, ray, angle);
	if (dis.discriminant < 0.00)
		return (hpa);
	hpa.distance = (-dis.b - sqrt(dis.discriminant)) / (2 * dis.a);
	hpb.distance = (-dis.b + sqrt(dis.discriminant)) / (2 * dis.a);
	hpa.hit = calc_vertex_normal(cone, ray, &hpa, angle);
	hpb.hit = calc_vertex_normal(cone, ray, &hpb, angle);
	if (hpa.hit == 0 && hpb.hit == 0)
		return (hpa);
	if (hpa.hit == 0 || (hpb.hit && hpa.distance > hpb.distance))
		hpa = hpb;	
	hpa.color = cone.color;
	ray_from_inside = is_point_inside_cone(*ray.origin, cone);
	if (hpa.hit && ray_from_inside && printf("hit from inside"))
		hpa.surface_normal_of_hittable = vec3_scale(hpa.surface_normal_of_hittable, -1);
	return (hpa);
}
