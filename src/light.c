/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:04:27 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/23 18:39:52 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	create_light(t_vector3 pos, float brightness, unsigned int color)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	light.color = color;
	light.next = NULL;
	ft_printf("light created\n");
	return (light);
}

void	add_light(t_light **lightlist, t_light *new)
{
	t_light	*l;

	if (!*lightlist)
		*lightlist = new;
	else
	{
		l = *lightlist;
		while (l->next)
			l = l->next;
		l->next = new;
	}
}

t_ambient	create_ambient(float brightness, unsigned int color)
{
	t_ambient	ambient;

	ambient.brightness = brightness;
	ambient.color = color;
	ft_printf("ambient created\n");
	return (ambient);
}
