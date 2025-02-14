/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:32 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 20:14:33 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minirt.h"

typedef struct	s_ambient
{
	float		ratio;
	t_vec3		rgb;
}				t_ambient;

typedef struct s_sphere
{ 
	t_vec3			position;
	float			radius;
	float			diameter;
	t_vec3			color;
	int				index;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_cylinder
{ 
	struct s_cylinder	*next;
	t_vec3				normal;
	t_vec3				position;
	float				radius;
	float				diameter;
	float				height;
	t_vec3				color;
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
	t_vec3		position;
	t_vec3		normal;
	float		fov;
} t_camera;

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
