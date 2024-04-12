/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_parse_other.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:50:40 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/12 23:14:07 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_resolution(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 3 || !str_is_int(split[1], 1, 3000) || !str_is_int(split[2], 1, 3000))
	{
		ft_printf("Invalid resolution\n");
		free_array(split);
		return (-1);
	}
	data->width = ft_atoi(split[1]);
	data->height = ft_atoi(split[2]);
	free_array(split);
	return (0);

}

int	parse_ambient(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) != 3 || !is_float(split[1]) || !is_color3(split[2]))
	{
		ft_printf("Invaliid ambient\n");
		free_array(split);
		return (-1);
	}
	data->ambient = create_ambient(ft_atof(split[1]), parse_color(split[2]));
	free_array(split);
	if (data->ambient.brightness < 0 || data->ambient.brightness > 1)
		return (-1);
	return (0);
}

int	parse_light(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (array_len(split) < 3 || !is_vector3(split[1]) || !is_float(split[2]))
	{
		ft_printf("Invalid light\n");
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

int	parse_camera(char *line, t_data *data)
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
	if (!is_vector3(split[1]) || !is_normal3(split[2]) || !str_is_int(split[3], 0, 180))
	{
		ft_printf("Invalid camera\n");
		free_array(split);
		return (-1);
	}
	create_camera(data, parse_vector3(split[1]),
			parse_vector3(split[2]), ft_atof(split[3]));
	free_array(split);
	return (0);
}
