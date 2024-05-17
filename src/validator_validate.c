/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:17:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/05/17 11:02:31 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_float(char *str)
{
	int	i;
	int	dot;

	if (!str)
		return (err("Invalid float: NULL", NULL) + 1);
	i = 0;
	dot = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && dot < 2)
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (err("Invalid float: Non-digits", NULL) + 1);
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		return (err("Invalid float: Multiple dots", NULL) + 1);
	return (1);
}

int	is_vector3(char *str)
{
	char		**split;
	int			ret;

	ret = 0;
	split = ft_split(str, ',');
	if (!split)
		return (0);
	if (array_len(split) != 3)
		ret = -1;
	if (!is_float(split[0]) || !is_float(split[1]) || !is_float(split[2]))
		ret = -2;
	if (ret == 0 && (fabs(ft_atof(split[0])) > MAXPOS || fabs(ft_atof(split[1]))
			> MAXPOS || fabs(ft_atof(split[2])) > MAXPOS))
		ret = -3;
	free_array(split);
	if (ret == -1)
		return (err("Invalid vector: expected x,y,z", NULL) + 1);
	if (ret == -2)
		return (err("Invalid vector: Illegal values", NULL) + 1);
	if (ret == -3)
		return (err("Invalid vector: Each component (x,y,z) "
				"must not exceed 10.000", NULL) + 1);
	return (1);
}

int	is_normal3(char *str)
{
	char	**split;
	int		i;
	double	hasvalue;

	hasvalue = 0;
	split = ft_split(str, ',');
	if (!split)
		return (0);
	i = 0;
	if (array_len(split) != 3)
		i = 10;
	while (i < 3)
	{
		if (!is_float(split[i]) || ft_atof(split[i]) < -1
			|| ft_atof(split[i]) > 1)
			break ;
		hasvalue += fabs(ft_atof(split[i]));
		i++;
	}
	free_array(split);
	if (!hasvalue || i != 3)
		err("Invalid normal", NULL);
	return (hasvalue && i == 3);
}

int	is_color3(char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	i = 0;
	if (array_len(split) != 3)
		i = 10;
	while (i < 3)
	{
		if (!is_float(split[i]))
			break ;
		if (ft_atof(split[i]) < 0 || ft_atof(split[i]) > 255)
			break ;
		i++;
	}
	free_array(split);
	if (i != 3)
		err("Invalid color", NULL);
	return (i == 3);
}

int	is_color6(char *str)
{
	char	**split;
	int		i;
	int		argc;

	split = ft_split(str, ';');
	if (!split)
		return (0);
	argc = array_len(split);
	i = 0;
	if (argc < 1 || argc > 2)
		i = 10;
	while (i < argc)
	{
		if (!is_color3(split[i]))
			i = 10;
		i++;
	}
	free_array(split);
	if (argc < 1 || argc > 2)
		err("Invalid color", NULL);
	return (i == argc);
}
