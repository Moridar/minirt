/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:36:47 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/24 23:50:34 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	parse_vector3(char *str)
{
	t_vector3	vector;
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return ((t_vector3){0, 0, 0});
	if (array_len(split) != 3)
	{
		free_array(split);
		return ((t_vector3){0, 0, 0});
	}
	vector.x = ft_atof(split[0]);
	vector.y = ft_atof(split[1]);
	vector.z = ft_atof(split[2]);
	free_array(split);
	return (vector);
}

int	parse_color(char *str)
{
	char	**split;
	int		red;
	int		green;
	int		blue;
	int		color;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	if (array_len(split) != 3)
	{
		free_array(split);
		return (0);
	}
	red = ft_atof(split[0]);
	green = ft_atof(split[1]);
	blue = ft_atof(split[2]);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	free_array(split);
	return (color);
}
