/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 01:04:19 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/09 12:50:50 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

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
	char	*trimmedline;
	int		ret;

	ft_printf("==Loading %s==\n", file);
	ret = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (ret >= 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		replace_whitespace_to_space(line);
		trimmedline = ft_strtrim(line, " ");
		free(line);
		ret = parse_line(trimmedline, data);
		free(trimmedline);
	}
	close(fd);
	if (ret < 0)
		ft_printf("Invalid file\n");
	return (ret);
}
