/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:30:45 by descamil          #+#    #+#             */
/*   Updated: 2025/01/24 11:54:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_vec3	ft_clamp(t_vec3 color)
{
	if (color.x < 0.0f)
		color.x = 0.0f;
	else if (color.x > 1.0f)
		color.x = 1.0f;

	if (color.y < 0.0f)
		color.y = 0.0f;
	else if (color.y > 1.0f)
		color.y = 1.0f;

	if (color.z < 0.0f)
		color.z = 0.0f;
	else if (color.z > 1.0f)
		color.z = 1.0f;

	return (color);
}

t_vec3	ft_create_vec3(float a, float b, float c)
{
	t_vec3	result;

	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}

t_vec3	ft_float_to_vec3(float a)
{
	t_vec3	result;

	result.x = a;
	result.y = a;
	result.z = a;
	return (result);
}

float	ft_dot(t_vec3 a, t_vec3 b)
{
	float result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;

	return (result);
}
t_vec3	ft_normalice(t_vec3 vec)
{
	float	magnitud;

	magnitud = ft_dot(vec, vec);
	magnitud = sqrt(magnitud);

	if (magnitud == 0.0f)
		return (vec);

	vec.x /= magnitud;
	vec.y /= magnitud;
	vec.z /= magnitud;

	return (vec);
}

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	if (b < a)
		return (b);
	return (0.0f);
}
