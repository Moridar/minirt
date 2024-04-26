/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_hitable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:59:56 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/27 01:53:27 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cone(char *line, t_data *data)
{
	t_hitable	cone;
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) < 6 || !is_vector3(split[1]) || !is_normal3(split[2])
		|| !is_float(split[3]) || !is_float(split[4]) || !is_color3(split[5]))
	{
		ft_printf("Invalid cone\n");
		free_array(split);
		return (-1);
	}
	cone = create_cone(parse_vector3(split[1]), parse_vector3(split[2]),
			ft_atof(split[3]), ft_atof(split[4]));
	cone.color = parse_color(split[5]);
	free_array(split);
	add_hitable(&data->hitables, cone);
	return (0);
}

int	parse_sphere(char *line, t_data *data)
{
	t_hitable	sphere;
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) < 4 || !is_vector3(split[1]) || !is_float(split[2])
		|| !is_color3(split[3]))
	{
		ft_printf("Invalid sphere\n");
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
	if (array_len(split) < 6 || !is_vector3(split[1]) || !is_normal3(split[2])
		|| !is_float(split[3]) || !is_float(split[4]) || !is_color3(split[5]))
	{
		ft_printf("Invalid cylinder\n");
		free_array(split);
		return (-1);
	}
	cylinder = create_cylinder(parse_vector3(split[1]), parse_vector3(split[2]),
			ft_atof(split[3]), ft_atof(split[4]));
	cylinder.color = parse_color(split[5]);
	free_array(split);
	add_hitable(&data->hitables, cylinder);
	return (0);
}

int	parse_plane(char *line, t_data *data)
{
	t_hitable	plane;
	char		**split;
	int			argc;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	argc = array_len(split);
	if (argc < 4 || !is_vector3(split[1]) || !is_normal3(split[2])
		|| !is_color6(split[3]) || (argc >= 5 && !is_float(split[4])))
	{
		ft_printf("Invalid plane");
		free_array(split);
		return (-1);
	}
	plane = create_plane(parse_vector3(split[1]),
			parse_vector3(split[2]));
	parse_color2(split[3], &plane.color, &plane.color1);
	if (argc >= 5)
		plane.checker_size = fmax(0, ft_atof(split[4]));
	free_array(split);
	add_hitable(&data->hitables, plane);
	return (0);
}
