/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:55 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/09 16:40:14 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(t_color c)
{
	return ((c.r << 24) + (c.g << 16) + (c.b << 8) + c.a);
}

t_color	scale_color(t_color c, float scale)
{
	c.r = (float)c.r * scale;
	c.g = (float)c.g * scale;
	c.b = (float)c.b * scale;
	c.a = c.a;
	return (c);
}

t_color	make_color(int a)
{
	t_color c;

	if (a < 0)
	{
		c.r = 128;
		a = -a;
	}
	c.a = a % 256;
	a -= c.a;
	a /= 256;
	c.b = a % 256; 
	a -= c.b;
	a /= 256;
	c.g = a % 256; 
	a -= c.g;
	a /= 256;
	c.r += a % 128;
	return (c);
}
