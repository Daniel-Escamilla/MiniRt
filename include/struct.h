/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:56 by descamil          #+#    #+#             */
/*   Updated: 2025/01/31 19:31:10 by descamil         ###   ########.fr       */
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

typedef struct
{
	float	x;
	float	y;
} 		t_vec2;

typedef union u_vec3
{
	struct
	{
		float		r;
		float		g;
		float		b;
	};
	struct
	{
		float		x;
		float		y;
		float		z;
	};
	struct
	{
		float		v1;
		float		v2;
		float		v3;
	};
}					t_vec3;

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
	int		inter;
	float	intersection;
	int		shadow;
	t_vec3	axis;
	t_vec3	to_hit;
	t_tt	tt;
	t_vec3	projection;
	
}			t_cy_formula;

// typedef struct
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	a;
// } 		t_vec4;

typedef struct s_cuadratic
{
	float	a;
	float	b;
	float	c;
	float	tt;
	float	disc;
	t_vec3	test;
}			t_cuadratic;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
}				t_keys;

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

typedef struct s_sphere
{ 
	t_vec3			position;
	float			radius;
	t_vec3			color;
	int				index;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_cylinder
{ 
	t_vec3				position;
	float				radius;
	float				height;
	t_vec3				color;
	t_vec3				normal;
	int					index;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct	s_plane
{
	t_vec3			position;
	t_vec3			normal;
	t_vec3			color;
	int				index;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_light
{
	int			count;
	int			direction;
	float		increment;
}				t_light;

typedef struct s_camera
{
	float		fov;
} t_camera;

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
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_ambient	*ambient;
	t_color		*color;
	t_light		*light;
	t_camera	*camera;
	t_keys		*keys;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	float		aspect_ratio;
	int			is_pressed;
    int			mouse_x;
    int			mouse_y;
	
}				t_image;

#endif
