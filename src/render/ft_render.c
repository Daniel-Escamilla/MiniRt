/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2024/10/24 20:04:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// uint8_t		r;
// uint8_t		g;
// r = (uint8_t)(coord.x * 255.0f);
// g = (uint8_t)(coord.y * 255.0f);
// color = 0x000000 | (r << 16) | (g << 8);
// return (color);

uint32_t	ft_convert_rgba(t_vec3 color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	
	r = (uint8_t)(color.x * 255.0f);
	g = (uint8_t)(color.y * 255.0f);
	b = (uint8_t)(color.z * 255.0f);
	return ((r << 16) | (g << 8) | b);
}

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

t_vec3	ft_dotv3(t_vec3 a, t_vec3 b, float (*operacion)(float, float))
{
	t_vec3	result;

	result.x = operacion(a.x, b.x);
	result.y = operacion(a.y, b.y);
	result.z = operacion(a.z, b.z);
	
	return (result);
}

t_vec3	ft_create_v3(float a)
{
	t_vec3	result;

	result.x = a;
	result.y = a;
	result.z = a;
	return (result);
}

t_vec3	ft_normalice(t_vec3 vec)
{
	float	magnitud;

	magnitud = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	magnitud = sqrt(magnitud);
	
	vec.x /= magnitud;
	vec.y /= magnitud;
	vec.z /= magnitud;

	return (vec);
}

float	ft_dot(t_vec3 a, t_vec3 b, int sign) //0 = +1, +2 | 1 = -1, +2 | 2 = +1, -2 | 3 = -1 y -2 
{
	float result;

	if (sign == 0)
		result = a.x * b.x + a.y * b.y + a.z * b.z;
	if (sign == 1)
		result = -a.x * b.x + -a.y * b.y + -a.z * b.z;
	if (sign == 2)
		result = a.x * -b.x + a.y * -b.y + a.z * -b.z;
	if (sign == 3)
		result = -a.x * -b.x + -a.y * -b.y + -a.z * -b.z;

	return (result);
}

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	if (b < a)
		return (b);
	return (0.0f);
}

t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_vec3		color;
	t_vec3		ray_dir;		// a
	t_vec3		ray_origin;		// b
	t_vec3		hit_point;
	float		discriminat;
	// t_result	result;
	// t_vec2		t;
	float		a;
	float		b;
	float		c;
	float		ratio;

	
	coord.x *= image->aspect_ratio;
	
	ray_dir.x = coord.x;
	ray_dir.y = coord.y;
	ray_dir.z = -1;

	ray_origin.x = 0.0f;
	ray_origin.y = 0.0f;
	ray_origin.z = 1.0f;

	
	// ( bx² ​+ by² ​+ bz² ​)t² + 2(ax​bx ​+ ay​by ​+ az​bz​)t + (ax²​ + ay² + az² − r²) = 0
	// a = ray_direction
	// b = ray_origin
	// r = radius
	// t = hit distant

	// b² - 4.0f * a * c;
	// (-b +- sqrt(discriminant)) / 2a

	ratio = 0.5f;
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = 2.0f * (ray_dir.x * ray_origin.x + ray_dir.y * ray_origin.y + ray_dir.z * ray_origin.z);
	c = (ray_origin.x * ray_origin.x + ray_origin.y * ray_origin.y + ray_origin.z * ray_origin.z) - ratio * ratio;

	discriminat = b * b - 4.0f * a * c;
	if (discriminat < 0)
	{
		color.x = 0.0f;
		color.y = 0.0f;
		color.z = 0.0f;
	}
	// float t0 = (-b + sqrt(discriminat)) / (2.0f * a);
	float closestt = (-b - sqrt(discriminat)) / (2.0f * a);

	color.x = 1.0f;
	color.y = 0.0f;
	color.z = 1.0f;
	
	
	hit_point = ft_dotv3(ray_origin, ft_dotv3 (ray_dir, ft_create_v3(closestt), ft_multiply), ft_add);
	
	t_vec3	normal = ft_normalice(hit_point);

	t_vec3	light_dir = ft_normalice(ft_create_v3(-1));


	float	d = ft_max(ft_dot(normal, light_dir, 2), 0.0f);

	// ft_print_vec3(hit_point);
	// color = ft_dotv3(ft_dotv3(normal, ft_create_v3(0.5f), ft_multiply), ft_create_v3(0.5f), ft_add);
	color = ft_dotv3(color, ft_create_v3(d), ft_multiply);

	return (color);
}

void	ft_create_render(t_mlx *data, t_image *image)
{
	t_vec3	color;
	t_vec2	coord;
	int		y;
	int		x;

	y = 0;
	
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			coord.x = ((float)x / (float)image->width);
			coord.y = ((float)y / (float)image->height) * -1 + 1;
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;
			color = ft_per_pixel(image, coord);
			color = ft_clamp(color);
			my_mlx_pixel_put(data, x, y, ft_convert_rgba(color));
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
