/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotv3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:31:55 by descamil          #+#    #+#             */
/*   Updated: 2025/02/04 17:48:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

float	ft_add(float a, float b)
{
	return (a + b);
}

float	ft_subtract(float a, float b)
{
	return (a - b);
}

float	ft_multiply(float a, float b)
{
	return (a * b);
}

float	ft_divide(float a, float b)
{
	if (b != 0)
		return (a / b);
	return (0);
}

t_vec3	ft_dotv3(t_vec3 a, t_vec3 b, float (*op)(float, float))
{
	t_vec3	result;

	result = ft_create_vec3(op(a.x, b.x), op(a.y, b.y), op(a.z, b.z));
	return (result);
}
