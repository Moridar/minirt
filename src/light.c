/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:04:27 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 01:42:55 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	create_light(t_vector3 pos, double brightness)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	return (light);
}

t_ambient	create_ambient(double brightness, unsigned int color)
{
	t_ambient	ambient;

	ambient.brightness = brightness;
	ambient.color = color;
	return (ambient);
}