/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:16:21 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/08 13:17:35 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	add_decimal(const char *str)
{
	float	i;
	float	n;

	i = 0;
	n = 10.0;
	while (ft_isdigit(*str))
	{
		i += (*str - '0') / n;
		n *= 10;
		str++;
	}
	return (i);
}

float	ft_atof(const char *str)
{
	float	i;
	int		sign;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign *= -1;
	i = 0;
	while (ft_isdigit(*str))
	{
		i = i * 10 + *str - '0';
		if (i < 0)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		str++;
	}
	if (*str == '.' || *str == ',')
		i += add_decimal(++str);
	return (i * sign);
}
