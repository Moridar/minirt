/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/26 20:06:31 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	mymlx_init(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 1);
	if (!data->mlx)
		exit(err(mlx_strerror(mlx_errno), NULL));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		destroy(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_key_hook(data->mlx, keydown, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_resize_hook(data->mlx, mlx_resize, data);
}

static void	data_init(t_data *data)
{
	data->width = 640;
	data->height = 360;
	data->hitables = NULL;
	data->light = NULL;
	data->camera.rays = NULL;
	data->mlx = NULL;
	ft_bzero(&data->ambient, sizeof(t_ambient));
	ft_bzero(&data->light, sizeof(t_light));
	ft_bzero(&data->camera, sizeof(t_camera));
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_printf("MiniRT by bsyvasal & dhorvath\n");
	if (argc == 1)
		return (err("No file input", NULL));
	if (argc > 2)
		return (err("Please only 1 file", NULL));
	data_init(&data);
	mymlx_init(&data);
	if (load_file(argv[1], &data) == -1)
		return (destroy(&data));
	draw(&data);
	mlx_loop(data.mlx);
	destroy(&data);
	return (0);
}
