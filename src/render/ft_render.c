/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2024/10/30 19:45:09 by descamil         ###   ########.fr       */
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

t_vec3	ft_create_vec3(float a, float b, float c)
{
	t_vec3	result;

	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}

t_vec3	ft_dotv3(t_vec3 a, t_vec3 b, float (*op)(float, float))
{
	t_vec3	result;

	result = ft_create_vec3(op(a.x, b.x), op(a.y, b.y), op(a.z, b.z));
	
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

	// ( bx² ​+ by² ​+ bz² ​)t² + 2(ax​bx ​+ ay​by ​+ az​bz​)t + (ax²​ + ay² + az² − r²) = 0
	// a = ray_direction
	// b = ray_origin
	// r = radius
	// t = hit distant

	// b² - 4.0f * a * c;
	// (-b +- sqrt(discriminant)) / 2a

	// radius = 0.5f;
t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_vec3		ray_dir;		// a
	t_vec3		ray_origin;		// b
	float		a;
	float		b;
	float		c;
	t_vec3		origin;
	float		closestt;
	int			found;
	
	t_vec3		rgb;
	coord.x *= image->aspect_ratio;

	ray_dir = ft_create_vec3(coord.x, coord.y, -1.0f);
	ray_origin = ft_create_vec3(0.0f, 0.0f, 3.0f);
	closestt = FLT_MAX;
	found = 0;
	t_sphere	*current = image->sphere;
	while (current)
	{
		t_vec3 test = ft_dotv3(ray_origin, current->position, ft_subtract); 
	
		a = ft_dot(ray_dir, ray_dir);
		b = 2.0f * ft_dot(ray_dir, test);
		c = ft_dot(test, test) - current->radius * current->radius;

		// float t0 = (-b + sqrt(discriminat)) / (2.0f * a);
		float disc = b * b - 4.0f * a * c;
		if (disc >= 0)
		{
			float	tt = (-b - sqrt(disc)) / (2.0f * a);
			if (tt < closestt)
			{
				origin = test;
				closestt = tt;
				rgb = current->color;
				found = 1;
			}
		}
		current = current->next;
		
	}
	if (found == 0)
		return (ft_float_to_vec3(0.0f));

	// Color base sin luz, [Magenta]
	// color = ft_create_vec3(1.0f, 0.0f, 1.0f);
	
	// t_vec3 hit_point = origin + ray_dir * closett; 
	t_vec3	hit_point = ft_dotv3(origin, ft_dotv3 (ray_dir, ft_float_to_vec3(closestt), ft_multiply), ft_add);
	

	// Normal, ajusta el rango de valores de -1.0f_1.0f a 0.0f_1.0f
	t_vec3	normal = ft_normalice(hit_point);
	
	// Representacion de los valores normal
	// color = normal * 0.5f + 0.5f;
	// color = ft_dotv3(ft_dotv3(normal, ft_float_to_vec3(0.5f), ft_multiply), ft_float_to_vec3(0.5f), ft_add);

	// t_vec3	test = ft_create_vec3(1.0f, -1.0f, 1.0f);
	// t_vec3	light_dir = ft_normalice(test);

	t_vec3	light_dir = ft_normalice(image->color->light_dir);

	light_dir = ft_dotv3(light_dir, ft_float_to_vec3(-1), ft_multiply);

	float	d = ft_max(ft_dot(normal, light_dir), 0.0f);


	t_vec3	direcctional_color = ft_dotv3(rgb, ft_float_to_vec3(d), ft_multiply);

	t_vec3 ambient_light = ft_float_to_vec3(0.02f);

	t_vec3 color = ft_dotv3(direcctional_color, ambient_light, ft_add);

	return (color);
}

# include <time.h>

void	ft_create_render(t_mlx *data, t_image *image)
{
	t_vec3	color;
	t_vec2	coord;
	int		y;
	int		x;

	clock_t start_time = clock();

	y = 0;
	while (y < image->height)
	{
		coord.y = ((float)y / (float)image->height) * -1 + 1;
		coord.y = coord.y * 2.0f - 1.0f;
		x = 0;
		while (x < image->width)
		{
			coord.x = ((float)x / (float)image->width);
			coord.x = coord.x * 2.0f - 1.0f;
			color = ft_per_pixel(image, coord);
			color = ft_clamp(color);
			my_mlx_pixel_put(data, x, y, ft_convert_rgba(color));
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
	clock_t end_time = clock();  // Finaliza la medición del tiempo
	double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // Calcula la duración en milisegundos
	printf("Tiempo de ejecución: %f ms\n", duration);  // Imprime el tiempo de ejecución
}
