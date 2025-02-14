/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:56 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:55:12 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../minirt.h"

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
	t_objects	*objects;
	t_mlx		*data;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	float		aspect_ratio;
	t_color		*color;
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
