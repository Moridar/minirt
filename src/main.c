/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/23 22:38:14 by bsyvasal         ###   ########.fr       */
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
	t_hitable	cyl;
	t_hitable	plane;
	t_light		l1;
	t_light		l2;

	create_camera(d, (t_vector3){0, 0, 0}, (t_vector3){0, 0, 1}, 90);
	d->ambient = create_ambient(0.1, 0xFFFFFFFF);
	d->light = NULL;
	l1 = create_light((t_vector3){0, 15, 0}, 0.8, 0xFFFFFFFF);
	//l2 = create_light((t_vector3){0, -15, 0}, 0.8, 0xFFFFFFFF);
	sphere = create_sphere((t_vector3){0, 0, 15}, 1.0f, 0x0000FFFF);
	cyl = create_cylinder((t_vector3){0, 1, 19}, vec3_unit((t_vector3){0, 1, 0.5}), 3, 7, 0xFF0000FF);
	plane = create_plane((t_vector3){0, 0, 20}, (t_vector3){0, 0, -1}, 0x00FF00FF);
	add_hitable(&d->hitables, cyl);
	add_hitable(&d->hitables, plane);
	add_hitable(&d->hitables, sphere);
	add_light(&d->light, l1);
//	add_light(&d->light, &l2);
	(void) l1;
	(void) l2;
	(void) plane;	
	(void) cyl;
	(void) sphere;
}

static void mymlx_init(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 0);
	if (!data->mlx)
		exit(print_msg(4));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		destroy(data);
	mlx_key_hook(data->mlx, keydown, data);
	mlx_loop_hook(data->mlx, mouse_hook, data);
	mlx_resize_hook(data->mlx, mlx_resize, data);
}

static void	data_init(t_data *data)
{
	data->width = 1920;
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
	if (argc == 1 && ft_printf("No file input, loading testdata\n"))
		testdata_init((&data));
	else if (load_file(argv[1], &data) == -1)
		return (destroy(&data));
	mymlx_init(&data);
	ft_printf("Window: [%d, %d]\n", data.width, data.height);
	draw(&data);
	mlx_loop(data.mlx);
	destroy(&data);
	return (0);
}
