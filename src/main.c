/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/05 15:39:47 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	print_msg(int msgno)
{
	if (msgno == 3)
		ft_printf("no data\n");
	if (msgno == 4)
		ft_printf("%s\n", mlx_strerror(mlx_errno));
	return (msgno);
}

static void	data_init(t_data *data)
{
	if (!data)
		exit(print_msg(3));
	data->width = 800;
	data->height = 600;
	data->mlx = mlx_init(data->width, data->height, "MiniRT", 1);
	if (!data->mlx)
		exit(print_msg(4));
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img || !data->win)
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
	draw(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}