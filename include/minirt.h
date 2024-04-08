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


// after we can just take the hit.color from each ray or if we dont want to store it we can just put it to screen immediately
// this is just another function we need to add to the objects. if we give it a point on the surface what the normalvector there is

typedef struct s_hitpoint
{
	t_vector3	pos;
	t_vector3	surface_normal_of_hittable;
	unsigned int	color;
}	t_hitpoint;

// we can get all the possible hits for each ray, and calc the distance after all the hits are created, and take the shortest.
//but we dont know if they hit the same object, 1 ray can hit 1 object once, yeah i just wonder if it doesnt hit anything, we just put the color to be black
//also after we start the ray towards the light the distance also has an impact, i dont thnik the distance matter, i would, it does, since the plane shpuld be infinite

// we can worry about this later, if something is off, same would be true for the plane, the angle changes, so i am wrong with the distance thing.
// we can just check if the hit is behind the light, if it is we dont need to check the light, we can just return the color of the hit object	

// I will fix camera, and then start the surface normals, they arent that bad, just the cylinder one is annoying
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
t_vector3	parse_vector3(char *str);
int			parse_color(char *str);
int			parse_sphere(char *line, t_data *data);
int			parse_plane(char *line, t_data *data);
int			parse_cylinder(char *line, t_data *data);

// MLX utils
void		draw(t_data *data);
void		keydown(void *data);
void		mouse_hook(void *data);
int			destroy(t_data *data);

#endif