/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:56 by descamil          #+#    #+#             */
/*   Updated: 2024/10/23 23:18:11 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../minirt.h"

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

typedef struct s_image
{
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	float	aspect_ratio;
}			t_image;

typedef struct	s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlx;


#endif
