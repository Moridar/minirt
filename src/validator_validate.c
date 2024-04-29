/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:17:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/29 11:23:23 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_float(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && dot < 2)
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
		{
			printf("1Invalid float\n");
			return (0);
		}
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
	{
		printf("2Invalid float\n");
		return (0);
	}
	return (1);
}

int	is_vector3(char *str)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	if (array_len(split) != 3)
	{
		free_array(split);
		ft_printf("1Invalid vector\n");
		return (0);
	}
	if (!is_float(split[0]) || !is_float(split[1]) || !is_float(split[2]))
	{
		ft_printf("2Invalid vector\n");
		free_array(split);
		return (0);
	}
	free_array(split);
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
		if (!is_float(split[i]))
			i = 10;
		if (ft_atof(split[i]) < -1 || ft_atof(split[i]) > 1)
			i = 10;
		hasvalue += fabs(ft_atof(split[i]));
		i++;
	}
	free_array(split);
	if (hasvalue != 0 && i == 3)
		return (1);
	ft_printf("Invalid normal\n");
	return (0);
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
			i = 10;
		if (ft_atof(split[i]) < 0 || ft_atof(split[i]) > 255)
			i = 10;
		i++;
	}
	free_array(split);
	if (i == 3)
		return (1);
	ft_printf("Invalid color\n");
	return (0);
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
	if (i == argc)
		return (1);
	ft_printf("Invalid color\n");
	return (0);
}
