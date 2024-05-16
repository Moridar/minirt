/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_hitable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:59:56 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/05/16 11:32:44 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_special(t_hitable *hit, char **split)
{
	while (*split)
	{
		if (ft_strncmp(*split, "chk:", 4) == 0)
		{
			if (!is_float(*split + 4))
				return (-1);
			hit->checker_size = fmax(0, ft_atof(*split + 4));
		}
		split++;
	}
	return (1);
}

int	parse_cone(char *line, t_data *data)
{
	t_hitable	cone;
	char		**split;
	int			argc;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	argc = array_len(split);
	if (argc < 6 || !is_vector3(split[1]) || !is_normal3(split[2])
		|| !is_float(split[3]) || !is_float(split[4]) || !is_color6(split[5]))
	{
		free_array(split);
		return (err("Invalid cone", NULL) + 1);
	}
	cone = create_cone(parse_vector3(split[1]), parse_vector3(split[2]),
			ft_atof(split[3]), ft_atof(split[4]));
	parse_color2(split[5], &cone.color, &cone.color1);
	if (argc >= 6)
		argc = parse_special(&cone, split + 6);
	free_array(split);
	if (argc == -1 || cone.diameter <= 0 || cone.height <= 0
		|| !validate_normal(cone.normal))
		return (err("Invalid cone", NULL));
	add_hitable(&data->hitables, cone);
	return (0);
}

int	parse_sphere(char *line, t_data *data)
{
	t_hitable	sphere;
	char		**split;
	int			argc;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	argc = array_len(split);
	if (argc < 4 || !is_vector3(split[1]) || !is_float(split[2])
		|| !is_color6(split[3]))
	{
		free_array(split);
		return (err("Invalid sphere", NULL));
	}
	sphere = create_sphere(parse_vector3(split[1]),
			ft_atof(split[2]));
	parse_color2(split[3], &sphere.color, &sphere.color1);
	if (argc >= 4)
		argc = parse_special(&sphere, split + 4);
	free_array(split);
	if (argc == -1 || !validate_normal(sphere.normal))
		return (err("Invalid sphere", NULL));
	add_hitable(&data->hitables, sphere);
	return (0);
}

int	parse_cylinder(char *line, t_data *data)
{
	t_hitable	cylinder;
	char		**split;
	int			argc;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	argc = array_len(split);
	if (argc < 6 || !is_vector3(split[1]) || !is_normal3(split[2])
		|| !is_float(split[3]) || !is_float(split[4]) || !is_color6(split[5]))
	{
		free_array(split);
		return (err("Invalid cylinder", NULL));
	}
	cylinder = create_cylinder(parse_vector3(split[1]), parse_vector3(split[2]),
			ft_atof(split[3]), ft_atof(split[4]));
	parse_color2(split[5], &cylinder.color, &cylinder.color1);
	if (argc >= 6)
		argc = parse_special(&cylinder, split + 6);
	free_array(split);
	if (argc == -1 || cylinder.diameter <= 0 || cylinder.height <= 0
		|| !validate_normal(cylinder.normal))
		return (err("Invalid cylinder", NULL));
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
		|| !is_color6(split[3]))
		argc = -1;
	else
	{
		plane = create_plane(parse_vector3(split[1]),
				parse_vector3(split[2]));
		parse_color2(split[3], &plane.color, &plane.color1);
	}
	if (argc >= 5)
		argc = parse_special(&plane, split + 4);
	free_array(split);
	if (argc == -1 || !validate_normal(plane.normal))
		return (err("Invalid plane", NULL));
	add_hitable(&data->hitables, plane);
	return (0);
}
