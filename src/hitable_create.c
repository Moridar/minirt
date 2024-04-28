/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:06:31 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/27 23:10:17 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitable	create_cone(t_vector3 pos, t_vector3 normal, float diameter,
				float height)
{
	t_hitable	hit;

	hit.type = 'o';
	hit.pos = pos;
	hit.normal = vec3_unit(normal);
	hit.diameter = diameter;
	hit.height = height;
	hit.color1 = 0xFF;
	hit.checker_size = 0;
	hit.next = NULL;
	ft_printf("cone created\n");
	return (hit);
}

t_hitable	create_sphere(t_vector3 pos, float diameter)
{
	t_hitable	hit;

	hit.type = 's';
	hit.pos = pos;
	hit.diameter = diameter;
	hit.color = 0;
	hit.color1 = 0xFF;
	hit.checker_size = 0;
	hit.next = NULL;
	ft_printf("sphere created\n");
	return (hit);
}

t_hitable	create_plane(t_vector3 pos, t_vector3 normal)
{
	t_hitable	hit;

	hit.type = 'p';
	hit.pos = pos;
	hit.normal = vec3_unit(normal);
	hit.color = 0;
	hit.color1 = 0xFF;
	hit.checker_size = 0;
	hit.next = NULL;
	ft_printf("plane created\n");
	return (hit);
}

t_hitable	create_cylinder(t_vector3 pos, t_vector3 normal, float diameter,
				float height)
{
	t_hitable	hit;

	hit.type = 'c';
	hit.pos = pos;
	hit.normal = vec3_unit(normal);
	hit.diameter = diameter;
	hit.height = height;
	hit.color1 = 0xFF;
	hit.checker_size = 0;
	hit.next = NULL;
	ft_printf("cylinder created\n");
	return (hit);
}

void	add_hitable(t_hitable **list, t_hitable hit)
{
	t_hitable	*new;
	t_hitable	*tmp;

	new = ft_calloc(1, sizeof(t_hitable));
	if (!new)
		return ;
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
