/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/25 16:22:09 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	print_msg(int msgno)
{
	if (msgno == 3)
		ft_printf("no data\n");
	if (msgno == 4)
		ft_printf("%s\n", mlx_strerror(mlx_errno));
	return (msgno);
}

static void	mymlx_init(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 1);
	if (!data->mlx)
		exit(print_msg(4));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		destroy(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_key_hook(data->mlx, keydown, data);
	mlx_loop_hook(data->mlx, mouse_hook, data);
	mlx_resize_hook(data->mlx, mlx_resize, data);
}

static void	data_init(t_data *data)
{
	data->width = 1080;
	data->height = 1080;
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

	if (argc && argv[0])
		ft_printf("MiniRT\n");
	data_init(&data);
	if (argc == 1)
		return (err("No file input", NULL));
	mymlx_init(&data);
	if (load_file(argv[1], &data) == -1)
		return (destroy(&data));
	ft_printf("Window: [%d, %d]\n", data.width, data.height);
	draw(&data);
	mlx_loop(data.mlx);
	destroy(&data);
	return (0);
}
