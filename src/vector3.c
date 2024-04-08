/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:12:13 by dhorvath          #+#    #+#             */
/*   Updated: 2024/04/05 14:00:22 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float distance(t_vector3 from, t_vector3 to)
{
	return (sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2)
				+ pow(to.z - from.z, 2)));
}

float magnitude(t_vector3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}