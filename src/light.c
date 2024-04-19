/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:04:27 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/19 11:41:23 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	create_light(t_vector3 pos, float brightness, unsigned int color)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	light.color = color;
	ft_printf("light created\n");
	return (light);
}

t_ambient	create_ambient(float brightness, unsigned int color)
{
	t_ambient	ambient;

	ambient.brightness = brightness;
	ambient.color = color;
	ft_printf("ambient created\n");
	return (ambient);
}