/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:56 by descamil          #+#    #+#             */
/*   Updated: 2024/10/30 16:00:33 by descamil         ###   ########.fr       */
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

typedef struct
{
	float	x;
	float	y;
	float	z;
} 		t_vec3;

// typedef struct
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	a;
// } 		t_vec4;



typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
}				t_keys;

typedef struct s_color
{
	t_vec3		rgb;// red = x // green = y // blue = z
	t_vec3		light_dir;
	int			plus;
}				t_color;

typedef struct s_sphere
{ 
	t_vec3			position;
	float			radius;
	t_vec3			color;
	struct s_sphere	*next;
}					t_sphere;

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
