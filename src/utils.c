/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:13:55 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/10 14:56:51 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int err(char *msg, char *arg)
{
	ft_printf("Error: %s", msg);
	if (arg)
		ft_printf(": %s", arg);
	ft_printf("\n");
	return (-1);
}

void	replace_whitespace_to_space(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			*str = ' ';
		++str;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}