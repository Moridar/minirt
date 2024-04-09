/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:50 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/09 12:07:59 by bsyvasal         ###   ########.fr       */
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

void	keydown(mlx_key_data_t keydata, void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		ft_printf("button R pressed\n");
	}
	if (keydata.key == MLX_KEY_KP_ADD)
	{
		data->camera.degree += 1;
		if (data->camera.degree > 180)
			data->camera.degree = 180;
		ft_printf("Camera.FOV increased to %d\n", data->camera.degree);
	}
	if (keydata.key == MLX_KEY_KP_SUBTRACT)
	{
		data->camera.degree -= 1;
		if (data->camera.degree < 0)
			data->camera.degree = 0;
		ft_printf("Camera.FOV decreased to %d\n", data->camera.degree);
	}
	if (keydata.key == MLX_KEY_KP_ENTER && keydata.action == MLX_PRESS)
	{
		data->camera = create_camera(data, data->camera.pos, data->camera.normal, data->camera.degree);
		ft_printf("Redrawing\n");
		draw(data);
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
