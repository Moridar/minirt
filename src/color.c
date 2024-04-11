/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:55 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/11 12:50:32 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(t_color c)
{
	return ((c.r << 24) + (c.g << 16) + (c.b << 8) + c.a);
}
t_color	make_color(unsigned int a)
{
	t_color c;

	c.a = a % 256;
	a /= 256;
	c.b = a % 256; 
	a /= 256;
	c.g = a % 256; 
	a /= 256;
	c.r = a;
	return (c);
}

int	scale_color(int color, float scale)
{
	t_color c;

	c = make_color(color);
	c.r = (float)c.r * scale;
	if (c.r > 255)
		c.r = 255;
	c.g = (float)c.g * scale;
	if (c.g > 255)
		c.g = 255;
	c.b = (float)c.b * scale;
	if (c.b > 255)
		c.b = 255;
	c.a = c.a;
	return (get_color(c));
}

