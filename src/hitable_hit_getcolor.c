/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_hit_getcolor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:37:40 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/05/17 00:39:27 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pixelcolor(mlx_image_t *img, float xf, float yf)
{
	int		x;
	int		y;
	uint8_t	*pixelstart;

	x = ((int)((1 - xf) * img->width) + img->width / 2) % img->width;
	y = (int)((1 - yf) * img->height) % img->height;
	if (0 <= x && x < (int) img->width && 0 <= y && y < (int) img->height)
	{
		pixelstart = img->pixels + (y * img->width + x) * sizeof(int32_t);
		return (*(pixelstart) << 24 | *(pixelstart + 1) << 16
			| *(pixelstart + 2) << 8 | *(pixelstart + 3));
	}
	return (0xFF);
}

int	getcolor_sphere(t_hitable *obj, t_hitpoint *hp)
{
	float	u;
	float	v;
	int		x;
	int		y;

	if (obj->checker_size <= 0 && !obj->bmp)
		return (obj->color);
	u = atan2(hp->normal.z, hp->normal.x) / (2.0 * M_PI) * obj->diameter;
	v = asin(hp->normal.y) / M_PI * obj->diameter;
	if (obj->bmp)
		return (get_pixelcolor(obj->bmp, u, v));
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

	if (obj->checker_size <= 0 && !obj->bmp)
		return (obj->color);
	e = vec3_unit(vec3_cross(obj->normal, (t_vector3){1, 0, 0}));
	if (vec3_length(e) < 0.01)
		e = vec3_unit(vec3_cross(obj->normal, (t_vector3){0, 0, 1}));
	u = vec3_dot(hp->pos, e);
	e = vec3_unit(vec3_cross(obj->normal, e));
	v = vec3_dot(hp->pos, e);
	if (obj->bmp)
		return (get_pixelcolor(obj->bmp, u, v));
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

	if (obj->checker_size <= 0 && !obj->bmp)
		return (obj->color);
	angle = vec3_dot(vec3_unit(vec3_cross(vec3_scale(obj->normal, -1),
					(t_vector3){0, 0, 1})), hp->normal);
	u = acos(angle) * obj->diameter * 2 / M_PI;
	v = vec3_dot(vec3_sub(hp->pos, obj->pos), obj->normal)
		/ (1 - vec3_dot(hp->normal, obj->normal));
	if (obj->bmp)
		return (get_pixelcolor(obj->bmp, u, v));
	x = u / obj->checker_size;
	y = v / obj->checker_size;
	if ((y + x) % 2 == 0)
		return (obj->color1);
	return (obj->color);
}
