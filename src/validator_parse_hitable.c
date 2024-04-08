/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_hitable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:59:56 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/08 14:03:14 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char *line, t_data *data)
{
	t_hitable	sphere;
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 4)
	{
		free_array(split);
		return (-1);
	}
	sphere = create_sphere(parse_vector3(split[1]),
			ft_atof(split[2]), parse_color(split[3]));
	free_array(split);
	add_hitable(&data->hitables, sphere);
	return (0);
}

int	parse_cylinder(char *line, t_data *data)
{
	t_hitable	cylinder;
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 6)
	{
		free_array(split);
		return (-1);
	}
	cylinder = create_cylinder(parse_vector3(split[1]),
			parse_vector3(split[2]), ft_atof(split[3]),
			ft_atof(split[4]), parse_color(split[5]));
	free_array(split);
	add_hitable(&data->hitables, cylinder);
	return (0);
}

int	parse_plane(char *line, t_data *data)
{
	t_hitable	plane;
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 4)
	{
		free_array(split);
		return (-1);
	}
	plane = create_plane(parse_vector3(split[1]),
			parse_vector3(split[2]), parse_color(split[3]));
	free_array(split);
	add_hitable(&data->hitables, plane);
	return (0);
}
