/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:55 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/11 15:23:18 by bsyvasal         ###   ########.fr       */
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

int color_add(int a, int b, int c)
{
	t_color color;
	t_color color2;
	t_color color3;

	color = make_color(a);
	color2 = make_color(b);
	color3 = make_color(c);
	color.r = color.r + color2.r + color3.r;
	if (color.r > 255)
		color.r = 255;
	color.g = color.g + color2.g + color3.g;
	if (color.g > 255)
		color.g = 255;
	color.b = color.b + color2.b + color3.b;
	if (color.b > 255)
		color.b = 255;
	color.a = color.a + color2.a + color3.a;
	if (color.a > 255)
		color.a = 255;
	return (get_color(color));
}

int color_multiply(int a, int b)
{
	t_color color;
	t_color color2;

	color = make_color(a);
	color2 = make_color(b);
	color.r = (color.r * color2.r) / 255;
	color.g = (color.g * color2.g) / 255;
	color.b = (color.b * color2.b) / 255;
	color.a = (color.a * color2.a) / 255;
	return (get_color(color));
}