/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:04:27 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 01:05:11 by bsyvasal         ###   ########.fr       */
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

t_ambient	create_ambient(double brightness)
{
	t_ambient	ambient;

	ambient.brightness = brightness;
	return (ambient);
}