/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:50 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/27 02:38:23 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	destroy(t_data *data)
{
	void	*tmp;

	if (!data)
		exit(1);
	while (data->hitables)
	{
		tmp = data->hitables;
		data->hitables = data->hitables->next;
		free(tmp);
	}
	while (data->light)
	{
		tmp = data->light;
		data->light = data->light->next;
		free(tmp);
	}
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
}

void	loop_hook(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (data->changed)
		draw(data);
	if (data->img->instances[0].x
		!= (data->mlx->width - (int)data->img->width) / 2
		|| data->img->instances[0].y
		!= (data->mlx->height - (int)data->img->height) / 2)
		reposition(data);
}

void	mlx_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;
	float	ratio;
	float	newratio;

	data = (t_data *)param;
	ratio = (float) data->width / data->height;
	newratio = (float) width / height;
	if ((height > (int) data->img->height && width == (int) data->img->width)
		|| (width > (int) data->img->width && height
			== (int) data->img->height))
		return ;
	if (newratio > ratio)
		width = height * ratio;
	else
		height = width / ratio;
	mlx_resize_image(data->img, width, height);
	data->changed = 1;
}
