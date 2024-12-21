/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2024/12/21 20:20:15 by descamil         ###   ########.fr       */
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
int ft_ray_sphere_intersection(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere, float *closestt, t_vec3 *rgb, t_vec3 *origin)
{
	t_vec3 test = ft_dotv3(ray_origin, sphere->position, ft_subtract);
	float a = ft_dot(ray_dir, ray_dir);
	float b = 2.0f * ft_dot(ray_dir, test);
	float c = ft_dot(test, test) - sphere->radius * sphere->radius;
	float disc = b * b - 4.0f * a * c;

	if (disc >= 0)
	{
		float tt = (-b - sqrt(disc)) / (2.0f * a);
		if (tt < *closestt)
		{
			*closestt = tt;
			*origin = test;
			*rgb = sphere->color;
			return 1;
		}
	}
	return 0;
}

int ft_ray_cylinder_intersection(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin)
{
    t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
    float a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
    float b = 2.0f * (ray_dir.x * to_cyl.x + ray_dir.z * to_cyl.z);
    float c = to_cyl.x * to_cyl.x + to_cyl.z * to_cyl.z - cylinder->radius * cylinder->radius;
    float disc = b * b - 4.0f * a * c;
    int intersect_with_body = 0;
    int intersect_with_bottom = 0;
    int intersect_with_top = 0;

    // Intersección con el cuerpo del cilindro
    if (disc >= 0.0f)
    {
        float t = (-b - sqrt(disc)) / (2.0f * a);
        if (t < *closest_t && t > 0.0f)
        {
            float y_intersection = to_cyl.y + t * ray_dir.y;
            float ymin = -cylinder->height / 2.0f;
            float ymax = cylinder->height / 2.0f;
            if (y_intersection > ymin && y_intersection < ymax)
            {
                *closest_t = t;
                *origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t), ft_multiply), ft_add);
                *rgb = cylinder->color;
                intersect_with_body = 1;
            }
        }
    }

    // Intersección con la tapa inferior
    if (fabs(ray_dir.y) > 1e-6) // Evitar división por cero
    {
        float t_bottom = (cylinder->position.y - cylinder->height / 2.0f - ray_origin.y) / ray_dir.y;
        if (t_bottom > 0.0f && t_bottom < *closest_t)
        {
            t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_bottom), ft_multiply), ft_add);
            if ((hit_point.x - cylinder->position.x) * (hit_point.x - cylinder->position.x) +
                (hit_point.z - cylinder->position.z) * (hit_point.z - cylinder->position.z) <= cylinder->radius * cylinder->radius)
            {
                *closest_t = t_bottom;
                hit_point.y = cylinder->position.y - cylinder->height / 2.0f;
                *origin = hit_point;
                *rgb = cylinder->color;
                intersect_with_bottom = 1;
            }
        }

        // Intersección con la tapa superior
        float t_top = (cylinder->position.y + cylinder->height / 2.0f - ray_origin.y) / ray_dir.y;
        if (t_top > 0.0f && t_top < *closest_t)
        {
            t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_top), ft_multiply), ft_add);
            if ((hit_point.x - cylinder->position.x) * (hit_point.x - cylinder->position.x) +
                (hit_point.z - cylinder->position.z) * (hit_point.z - cylinder->position.z) <= cylinder->radius * cylinder->radius)
            {
                *closest_t = t_top;
                hit_point.y = cylinder->position.y + cylinder->height / 2.0f;
                *origin = hit_point;
                *rgb = cylinder->color;
                intersect_with_top = 1;
            }
        }
    }
	
    return intersect_with_body || intersect_with_bottom || intersect_with_top;
}



t_vec3 ft_calculate_lighting(t_vec3 normal, t_vec3 rgb, t_image *image)
{
	t_vec3 light_dir = ft_normalice(image->color->light_dir);
	light_dir = ft_dotv3(light_dir, ft_float_to_vec3(-1), ft_multiply);
	float d = ft_max(ft_dot(normal, light_dir), 0.0f);
	t_vec3 directional_color = ft_dotv3(rgb, ft_float_to_vec3(d), ft_multiply);
	t_vec3 ambient_light = ft_float_to_vec3(0.05f);
	return ft_dotv3(directional_color, ambient_light, ft_add);
}

t_vec3 ft_per_pixel(t_image *image, t_vec2 coord)
{
    t_vec3 ray_dir;
    t_vec3 ray_origin;
    t_vec3 origin;
    float closestt;
    int found;
    t_vec3 rgb;
    t_sphere *current_sphere;
    t_cylinder *current_cylinder;
    t_vec3 hit_point;
    t_vec3 normal;

    coord.x *= image->aspect_ratio;
    ray_dir = ft_create_vec3(coord.x, coord.y, -1.0f);
    ray_origin = ft_create_vec3(0.0f, 0.0f, 3.0f);
    closestt = FLT_MAX;  // Inicializa la distancia más cercana
    found = 0;
    current_sphere = image->sphere;
    current_cylinder = image->cylinder;

    // Buscar intersección con cilindros
    while (current_cylinder)
    {
        if (ft_ray_cylinder_intersection(ray_origin, ray_dir, current_cylinder, &closestt, &rgb, &origin))
        {
            found = 1;
        }
        current_cylinder = current_cylinder->next;
    }

    // Buscar intersección con esferas
    while (current_sphere)
    {
        if (ft_ray_sphere_intersection(ray_origin, ray_dir, current_sphere, &closestt, &rgb, &origin))
        {
            found = 1;
        }
        current_sphere = current_sphere->next;
    }

    // Si no se encontró ninguna intersección, retornar negro
    if (found == 0)
        return ft_float_to_vec3(0.0f);

    // Calcular el punto de intersección más cercano
    hit_point = ft_dotv3(origin, ft_dotv3(ray_dir, ft_float_to_vec3(closestt), ft_multiply), ft_add);
    normal = ft_normalice(hit_point);  // Normal en el punto de intersección

    return ft_calculate_lighting(normal, rgb, image);  // Calcular iluminación
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
