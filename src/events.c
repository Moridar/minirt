/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:50 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 02:09:29 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	destroy(t_data *data)
{
	t_hitable	*tmp;

	if (!data)
		exit(1);
	while (data->hitables)
	{
		tmp = data->hitables;
		data->hitables = data->hitables->next;
		free(tmp);
	}
	if (data->camera.rays)
		free(data->camera.rays);
	if (data->mlx)
		mlx_terminate(data->mlx);
	exit(0);
	return (0);
}

void	keydown(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		ft_printf("button R pressed\n");
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
	{
		ft_printf("button 1 pressed\n");
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_2))
	{
		ft_printf("button 2 pressed\n");
	}
}

void	mouse_hook(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		ft_printf("Mouse 1 clicked\n");
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		ft_printf("Mouse 2 clicked\n");
	}
}
