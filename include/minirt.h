/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:08:41 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/04/27 02:00:43 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "libft.h"
# include "vec3.h"
# include <math.h>
# include <MLX42/MLX42.h>
# include <stdio.h>

typedef struct s_discriminant
{
	t_vector3	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
}	t_discrimininant;

typedef struct s_hitpoint
{
	t_vector3		pos;
	t_vector3		normal;
	unsigned int	color;
	int				hit;
	float			distance;
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
	unsigned int	color1;
	float			checker_size;
	void			*next;
}	t_hitable;

typedef struct s_light
{
	t_vector3		pos;
	float			brightness;
	unsigned int	color;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	float			brightness;
	unsigned int	color;
}	t_ambient;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	t_hitable	*hitables;
	t_light		*light;
	t_ambient	ambient;
	t_camera	camera;
	int			changed;
}				t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

// Creates
void			create_camera(t_data *data, t_vector3 pos,
					t_vector3 normal, int FOV);
t_ambient		create_ambient(float brightness, unsigned int color);
t_light			create_light(t_vector3 pos, float brightness,
					unsigned int color);
t_hitable		create_sphere(t_vector3 pos, float diameter,
					unsigned int color);
t_hitable		create_plane(t_vector3 pos, t_vector3 normal);
t_hitable		create_cylinder(t_vector3 pos, t_vector3 normal, float diameter,
					float height);
t_hitable		create_cone(t_vector3 pos, t_vector3 normal, float diameter,
					float height);
void			add_hitable(t_hitable **list, t_hitable hit);
void			add_light(t_light **lightlist, t_light light);

// Check hit
t_hitpoint		hit_hitable(t_hitable *list, t_ray ray);
t_hitpoint		hit_cone(t_hitable cone, t_ray ray);
t_hitpoint		hit_circle(t_hitable plane, t_ray ray, float radius);
t_hitpoint		hit_plane(t_hitable plane, t_ray ray);
int				calc_vertex_normal(t_hitable cone, t_ray ray,
					t_hitpoint *hp, float angle);

// Utils
void			free_array(char **array);
int				array_len(char **array);
void			replace_whitespace_to_space(char *str);
int				err(const char *msg, char *arg);

// Colors
int				color_add_light(t_hitpoint *hp, t_data *data);
int				color_scale(int color, float scale);
int				color_add(int a, int b, int c);
unsigned int	color_multiply(int a, int b);

//Parsing
int				load_file(char *file, t_data *data);
t_vector3		parse_vector3(char *str);
int				parse_color(char *str);
int				parse_color2(char *str, uint32_t *color, uint32_t *color1);
int				parse_sphere(char *line, t_data *data);
int				parse_plane(char *line, t_data *data);
int				parse_cylinder(char *line, t_data *data);
int				parse_cone(char *line, t_data *data);
int				parse_camera(char *line, t_data *data);
int				parse_light(char *line, t_data *data);
int				parse_ambient(char *line, t_data *data);
int				parse_resolution(char *line, t_data *data);

// Validator
int				is_vector3(char *str);
int				is_normal3(char *str);
int				is_color3(char *str);
int				is_color6(char *str);
int				is_float(char *str);
int				str_is_int(char *str, int min, int max);

// MLX utils
void			draw(t_data *data);
void			keydown(mlx_key_data_t keydata, void *params);
void			loop_hook(void *data);
int				destroy(t_data *data);
void			mlx_resize(int32_t width, int32_t height, void *param);
void			rerender(t_data *data);
void			reposition(t_data *data);

#endif
