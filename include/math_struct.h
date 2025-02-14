/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:16:20 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 20:17:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCT
# define MATH_STRUCT

# include "../minirt.h"

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

#endif 