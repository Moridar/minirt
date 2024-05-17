/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_hitable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:59:56 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/05/17 10:44:17 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_special(t_hitable *hit, char **split, t_data *data)
{
	mlx_texture_t	*bmp;
	char			*bmpfile;

	while (*split++)
	{
		if (ft_strncmp(*(split - 1), "chk:", 4) == 0)
		{
			if (!is_float(*(split - 1) + 4))
				return (-1);
			hit->checker_size = fmax(0, ft_atof(*(split - 1) + 4));
		}
		if (ft_strncmp(*(split - 1), "bmp:", 4) == 0)
		{
			bmpfile = ft_strjoin("./bumpmaps/", *(split - 1) + 4);
			bmp = mlx_load_png(bmpfile);
			free(bmpfile);
			if (!bmp)
				return (err("texture not found", NULL));
			hit->bmp = mlx_texture_to_image(data->mlx, bmp);
			mlx_delete_texture(bmp);
			if (!hit->bmp)
				return (err("text to img fails", NULL));
		}
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
		return (err("Invalid cone", NULL));
	}
	cone = create_cone(parse_vector3(split[1]), parse_vector3(split[2]),
			ft_atof(split[3]), ft_atof(split[4]));
	parse_color2(split[5], &cone.color, &cone.color1);
	if (argc >= 6)
		argc = parse_special(&cone, split + 6, data);
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
		argc = parse_special(&sphere, split + 4, data);
	free_array(split);
	if (argc == -1)
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
		argc = parse_special(&cylinder, split + 6, data);
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
		argc = parse_special(&plane, split + 4, data);
	free_array(split);
	if (argc == -1 || !validate_normal(plane.normal))
		return (err("Invalid plane", NULL));
	add_hitable(&data->hitables, plane);
	return (0);
}
