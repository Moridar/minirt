/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:55 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/26 18:55:02 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	get_color(t_color c)
{
	return ((c.r << 24) + (c.g << 16) + (c.b << 8) + c.a);
}

t_color	make_color(unsigned int a)
{
	t_color	c;

	c.a = a % 256;
	a /= 256;
	c.b = a % 256;
	a /= 256;
	c.g = a % 256;
	a /= 256;
	c.r = a;
	return (c);
}

int	color_scale(int color, float scale)
{
	t_color	c;

	c = make_color(color);
	if (scale > 1)
		scale = 1;
	if (scale < 0)
		scale = 0;
	c.r = (float)c.r * scale;
	c.g = (float)c.g * scale;
	c.b = (float)c.b * scale;
	return (get_color(c));
}

int	color_add(int a, int b, int c)
{
	t_color	color;
	t_color	color2;
	t_color	color3;

	color = make_color(a);
	color2 = make_color(b);
	color3 = make_color(c);
	color.r = fmin(color.r + color2.r + color3.r, 255);
	color.g = fmin(color.g + color2.g + color3.g, 255);
	color.b = fmin(color.b + color2.b + color3.b, 255);
	color.a = fmin(color.a + color2.a + color3.a, 255);
	return (get_color(color));
}

unsigned int	color_multiply(int a, int b)
{
	t_color	color;
	t_color	color2;

	color = make_color(a);
	color2 = make_color(b);
	color.r = (color.r * color2.r) / 255;
	color.g = (color.g * color2.g) / 255;
	color.b = (color.b * color2.b) / 255;
	color.a = (color.a * color2.a) / 255;
	return (get_color(color));
}
