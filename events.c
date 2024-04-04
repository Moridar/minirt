/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:50 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/04 14:08:51 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	destroy(t_data *data)
{
	if (!data)
		exit(1);
	if (data->img && data->mlx)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	keydown(int keycode, t_data *data)
{
	ft_printf("keydown registered: %d\n", keycode);
	if (keycode == 53)
		return (destroy(data));
	if (keycode == 15)
	{
		ft_printf("button R pressed\n");
	}
	else if (keycode == 18)
	{
		ft_printf("button 1 pressed\n");
	}
	else if (keycode == 19)
	{
		ft_printf("button 2 pressed\n");
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)data;
	if (button == 1)
	{
		ft_printf("Mouse 1 clicked\n");
	}
	if (button == 2)
	{
		ft_printf("Mouse 2 clicked\n");
	}
	if (button == 5)
		ft_printf("Mouse 5 clicked\n");
	if (button == 4)
		ft_printf("Mouse 4 clicked\n");
	return (0);
}
