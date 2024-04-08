/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 01:04:19 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/08 15:47:36 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static int	parse_ambient(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 3 || !is_float(split[1]) || !is_color3(split[2]))
	{
		free_array(split);
		return (-1);
	}
	data->ambient = create_ambient(ft_atof(split[1]), parse_color(split[2]));
	free_array(split);
	if (data->ambient.brightness < 0 || data->ambient.brightness > 1)
		return (-1);
	return (0);
}

static int	parse_light(char *line, t_data *data)
{
	char	**split;

	ft_printf("parsing light\n");
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 4 || !is_vector3(split[1]) || !is_float(split[2]))
	{
		free_array(split);
		return (-1);
	}
	data->light = create_light(parse_vector3(split[1]), ft_atof(split[2]));
	free_array(split);
	if (data->light.brightness < 0 || data->light.brightness > 1)
	{
		ft_printf("Invalid light brightness\n");
		return (-1);
	}
	return (0);
}

static int	parse_camera(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 4)
	{
		free_array(split);
		return (-1);
	}
	if (!is_vector3(split[1]) || !is_normal3(split[2]) || !is_fov(split[3]))
	{
		free_array(split);
		return (-1);
	}
	data->camera = create_camera(data, parse_vector3(split[1]),
			parse_vector3(split[2]), ft_atof(split[3]));
	free_array(split);
	return (0);
}

static int	parse_line(char *line, t_data *data)
{
	if (line[0] == 'A' && line[1] == ' ')
		return (parse_ambient(line, data));
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_camera(line, data));
	if (line[0] == 'L' && line[1] == ' ')
		return (parse_light(line, data));
	if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		return (parse_sphere(line, data));
	if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		return (parse_plane(line, data));
	if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		return (parse_cylinder(line, data));
	if (line[0] == '\0')
		return (0);
	return (-1);
}

int	load_file(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	ret = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ret = parse_line(line, data);
		free(line);
		if (ret < 0)
			break ;
	}
	close(fd);
	if (ret < 0)
		ft_printf("Invalid file\n");
	return (ret);
}
