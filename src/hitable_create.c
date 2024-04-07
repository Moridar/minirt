/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:06:31 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/07 22:20:24 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitable	create_sphere(t_vector3 pos, float diameter, unsigned int color)
{
	t_hitable	hit;

	hit.type = 's';
	hit.pos = pos;
	hit.diameter = diameter;
	hit.color = color;
	hit.next = NULL;
	return (hit);
}

t_hitable	create_plane(t_vector3 pos, t_vector3 normal, unsigned int color)
{
	t_hitable	hit;

	hit.type = 'p';
	hit.pos = pos;
	hit.normal = normal;
	hit.color = color;
	hit.next = NULL;
	return (hit);
}

t_hitable	create_cylinder(t_vector3 pos, t_vector3 normal, float diameter,
				float height, unsigned int color)
{
	t_hitable	hit;

	hit.type = 'c';
	hit.pos = pos;
	hit.normal = normal;
	hit.diameter = diameter;
	hit.height = height;
	hit.color = color;
	hit.next = NULL;
	return (hit);
}

void	add_hitable(t_hitable **list, t_hitable hit)
{
	t_hitable	*new;
	t_hitable	*tmp;

	new = ft_calloc(1, sizeof(t_hitable));
	*new = hit;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
