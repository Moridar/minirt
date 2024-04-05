/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/06 01:36:41 by bsyvasal         ###   ########.fr       */
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

	d->camera = create_camera(d, (t_vector3){0, 0, 0}, (t_vector3){0, 0, 1}, 90);
	ft_printf("camera created\n");
	d->ambient = create_ambient(0.2);
	ft_printf("ambient created\n");
	d->light = create_light((t_vector3){0, 0, 0}, 0.8);
	ft_printf("light created\n");
	sphere = create_sphere((t_vector3){10, 10, 0}, 2, 0xFF0000);
	ft_printf("sphere created\n");
	add_hitable(d->hitables, sphere);
	ft_printf("sphere added\n");
}

static void	data_init(t_data *data)
{
	if (!data)
		exit(print_msg(3));
	data->width = 800;
	data->height = 600;
	data->hitables = NULL;
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 1);
	if (!data->mlx)
		exit(print_msg(4));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		destroy(data);
	mlx_loop_hook(data->mlx, keydown, data);
	mlx_loop_hook(data->mlx, mouse_hook, data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc && argv[0])
		ft_printf("MiniRT\n");
	data_init(&data);
	testdata_init((&data));
	draw(&data);
	mlx_loop(data.mlx);
	destroy(&data);
	return (0);
}