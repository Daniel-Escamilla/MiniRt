/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:56 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 20:18:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../minirt.h"

# define M_PI_2 1.57079632679489661923	// (π / 2)
# define M_PI 3.14159265358979323846	// π

# define NEG 45
# define SUBS 65453
# define POS 43
# define PLUS 65451
# define A 97
# define B 98
# define C 99
# define D 100
# define E 101
# define F 102
# define G 103
# define H 104
# define I 105
# define J 106
# define K 107
# define L 108
# define M 109
# define N 110
# define O 111
# define P 112
# define Q 113
# define R 114
# define S 115
# define T 116
# define U 117
# define V 118
# define W 119
# define X 120
# define Y 121
# define Z 122

# define RIGHT D
# define LEFT A
# define UP W
# define DOWN S
# define FORWARD F
# define BACKWARD V

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
	int		*inter;
	float	intersection;
	int		shadow;
	t_vec3	axis;
	t_vec3	to_hit;
	t_tt	tt;
	t_vec3	projection;
	
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

typedef struct	s_mlx
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_image
{
	t_mlx		*data;
	t_objects	*objects;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	t_color		*color;
	float		aspect_ratio;
}				t_image;

typedef struct s_ray_values
{
	t_image		*current_image;
	t_objects	*current_objects;
	t_vec3		ray_origin;
	t_vec3		ray_dir;
	t_vec3		*origin;
	float		*tt;
	int			found;
}				t_ray_values;


#endif
