/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:08:41 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/04 13:10:43 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec3.h"
# include <math.h>
# include <MLX42/MLX42.h>
# include <stdio.h>

typedef struct s_hitpoint
{
	t_vector3	pos;
	t_vector3	surface_normal_of_hittable;
	unsigned int	color;
}	t_hitpoint;

typedef struct s_ray
{
	t_vector3	*origin;
	t_vector3	dir;
	t_hitpoint	hit;
}	t_ray;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	normal;
	int			degree;
	int			width;
	int			height;
	float		distance;
	t_ray		*rays;
}	t_camera;

typedef struct s_hitable
{
	char			type;
	t_vector3		pos;
	t_vector3		normal;
	float			diameter;
	float			height;
	unsigned int	color;
	void			*next;
}	t_hitable;

typedef struct s_light
{
	t_vector3	pos;
	float		brightness;
	//unsigned int			color;
}	t_light;

typedef struct s_ambient
{
	float			brightness;
	unsigned int	color;
}	t_ambient;

typedef struct s_data
{
	mlx_t		*mlx;
	void		*img;
	int			width;
	int			height;
	t_hitable	*hitables;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
}				t_data;

// Creates
t_camera	create_camera(t_data *data, t_vector3 pos,
				t_vector3 normal, int FOV);
t_ambient	create_ambient(float brightness, unsigned int color);
t_light		create_light(t_vector3 pos, float brightness);
void		add_hitable(t_hitable **list, t_hitable hit);
t_hitable	create_sphere(t_vector3 pos, float diameter, unsigned int color);
t_hitable	create_plane(t_vector3 pos, t_vector3 normal, unsigned int color);
t_hitable	create_cylinder(t_vector3 pos, t_vector3 normal, float diameter,
				float height, unsigned int color);

// Check hit
int			hit_hitable(t_hitable *list, t_ray ray);

// Array Utils
void		free_array(char **array);
int			array_len(char **array);

//Parsing
int			load_file(char *file, t_data *data);
t_vector3	parse_vector3(char *str);
int			parse_color(char *str);
int			parse_sphere(char *line, t_data *data);
int			parse_plane(char *line, t_data *data);
int			parse_cylinder(char *line, t_data *data);
int			parse_camera(char *line, t_data *data);
int			parse_light(char *line, t_data *data);
int			parse_ambient(char *line, t_data *data);

// Validator
int			is_vector3(char *str);
int			is_normal3(char *str);
int			is_color3(char *str);
int			is_float(char *str);
int			is_fov(char *str);

// MLX utils
void		draw(t_data *data);
void		keydown(void *data);
void		mouse_hook(void *data);
int			destroy(t_data *data);

#endif