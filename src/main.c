/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/09 11:47:32 by bsyvasal         ###   ########.fr       */
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

static void	testdata_init(t_data *d)
{
	t_hitable	sphere;

	d->camera = create_camera(d, (t_vector3){0, 0, 0}, (t_vector3){0, 0, 0}, 90);
	d->ambient = create_ambient(0.2, 0xFFFFFFFF);
	d->light = create_light((t_vector3){0, 0, 0}, 0.8);
	sphere = create_sphere((t_vector3){0, 0, 10}, 2.0, 0x0000FFFF);
	add_hitable(&d->hitables, sphere);
}

static void	data_init(t_data *data)
{
	if (!data)
		exit(print_msg(3));
	data->width = 800;
	data->height = 600;
	data->hitables = NULL;
	data->camera.rays = NULL;
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 1);
	if (!data->mlx)
		exit(print_msg(4));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		destroy(data);
	mlx_key_hook(data->mlx, keydown, data);
	mlx_loop_hook(data->mlx, mouse_hook, data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc && argv[0])
		ft_printf("MiniRT\n");
	data_init(&data);
	if (argc == 1 && ft_printf("No file input, loading testdata\n"))
		testdata_init((&data));
	else if (load_file(argv[1], &data) == -1)
		destroy(&data);
	ft_printf("Window: [%d, %d]\n", data.width, data.height);
	draw(&data);
	mlx_loop(data.mlx);
	destroy(&data);
	return (0);
}