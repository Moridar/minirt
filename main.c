/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:49:14 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/04 13:49:57 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	print_msg(int msgno)
{
	if (msgno == 4)
		ft_printf("data_init failed\n");
	return (msgno);
}

static void	f_init(t_data *data)
{
	if (!data)
		exit(print_msg(4));
	data->width = 800;
	data->height = 600;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(print_msg(4));
	data->win = mlx_new_window(data->mlx, data->width, data->height, "MiniRT");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img || !data->win)
		destroy(data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	mlx_hook(data->win, ON_DESTROY, 0, destroy, data);
	mlx_hook(data->win, ON_KEYDOWN, 0, keydown, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	print_msg(3);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc && argv[0])
		ft_printf("MiniRT\n");
	f_init(&data);
	mlx_loop(data.mlx);
	return (print_msg(1));
}
