/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:06:31 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/12 10:45:17 by bsyvasal         ###   ########.fr       */
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
	ft_printf("sphere created, color: %d, %d, %d\n", color >> 24, color >> 16, color >> 8);
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
	ft_printf("plane created: %d, %d, %d\n", color >> 24, (color >> 16) % 256, (color >> 8) % 256);
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
	ft_printf("cylinder created\n");
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
		ft_printf("^ added to a new list\n");
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	ft_printf("^ added to the existing list\n");
}
