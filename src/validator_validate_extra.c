/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_validate_extra.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:17:29 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/05/16 12:19:41 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	str_is_int(char *str, int min, int max)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (err("Invalid number: Non-digits", NULL) + 1);
		i++;
	}
	if (ft_atoi(str) < min || ft_atoi(str) > max)
		return (err("Number outside of range", NULL) + 1);
	return (1);
}

int	validate_normal(t_vector3 vec)
{
	if (isnan(vec.x) || isnan(vec.y) || isnan(vec.z))
	{
		err("Invalid normal: nan", NULL);
		return (0);
	}
	if (isinf(vec.x) || isinf(vec.y) || isinf(vec.z))
	{
		err("Invalid normal: inf", NULL);
		return (0);
	}
	return (1);
}
