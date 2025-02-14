/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:32 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:54:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minirt.h"

typedef struct s_tt
{
	float	tap1;
	float	tap2;
}			t_tt;

typedef struct s_cy_formula
{
	t_vec3	ray_origin;
	t_vec3	ray_dir;
	t_vec3	cy_pos;
	t_vec3	hit_point;
	t_vec3	to_cyl;
	t_vec3	axis;
	t_vec3	to_hit;
	t_vec3	projection;
	t_tt	tt;
	float	intersection;
	int		*inter;
	int		shadow;
}			t_cy_formula;

typedef struct s_cuadratic
{
	float	a;
	float	b;
	float	c;
	float	tt;
	float	disc;
	t_vec3	test;
}			t_cuadratic;

typedef struct s_color
{
	t_vec3		rgb;
	t_vec3		light_dir;
	int			plus;
}				t_color;

typedef struct	s_ambient
{
	float		ratio;
	t_vec3		rgb;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		normal;
	float		fov;
}				t_camera;

typedef struct s_light
{
	float		brightness;
	t_vec3		position;
	t_vec3		color;
}				t_light;

typedef struct s_sphere
{ 
	struct s_sphere	*next;
	t_vec3			position;
	float			diameter;
	float			radius;
	t_vec3			color;
}					t_sphere;

typedef struct	s_plane
{
	struct s_plane	*next;
	t_vec3			normal;
	t_vec3			position;
	t_vec3			color;
}				t_plane;

typedef struct s_cylinder
{ 
	struct s_cylinder	*next;
	t_vec3				normal;
	float				diameter;
	t_vec3				position;
	float				radius;
	float				height;
	t_vec3				color;
}						t_cylinder;

typedef struct s_objects
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_objects;

#endif
