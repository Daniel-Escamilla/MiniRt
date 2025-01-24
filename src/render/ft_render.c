/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2025/01/24 15:48:16 by descamil         ###   ########.fr       */
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

int	ft_ray_cylinder_intersection(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
	if (cylinder->normal.x == 1 && cylinder->normal.y == 0 && cylinder->normal.z == 0)
		return (ft_ray_cylinder_intersection_x(ray_origin, ray_dir, cylinder, closest_t, rgb, origin, normal));
	else if (cylinder->normal.x == 0 && cylinder->normal.y == 1 && cylinder->normal.z == 0)
		return (ft_ray_cylinder_intersection_y(ray_origin, ray_dir, cylinder, closest_t, rgb, origin, normal));
	return (ft_ray_cylinder_intersection_z(ray_origin, ray_dir, cylinder, closest_t, rgb, origin, normal));
}

t_vec3 ft_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}


int ft_ray_plane_intersection(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
    float denom = ft_dot(plane->normal, ray_dir);
    
    if (fabs(denom) < 1e-6)
        return 0;

    t_vec3 p0l0 = ft_dotv3(plane->position, ray_origin, ft_subtract);
    float t = ft_dot(p0l0, plane->normal) / denom;

    if (t < 0 || t > *closest_t)
        return 0;

    // Calcular el punto de intersección
    t_vec3 intersection = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t), ft_multiply), ft_add);

    *closest_t = t;
    *origin = intersection;
    *rgb = plane->color;
    *normal = plane->normal;

    if (ft_dot(*normal, ray_dir) > 0)
        *normal = ft_dotv3(*normal, ft_float_to_vec3(-1), ft_multiply);

    return 1;
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
	t_plane	*current_plane;
    t_vec3 hit_point;
    t_vec3 normal;

    coord.x *= image->aspect_ratio;
    ray_dir = ft_create_vec3(coord.x, coord.y, -1.0f);
    ray_origin = ft_create_vec3(0.0f, 0.0f, 3.0f);
    closestt = FLT_MAX;  // Inicializa la distancia más cercana
    found = 0;
    current_sphere = image->sphere;
    current_cylinder = image->cylinder;
	current_plane = image->plane;

    // Buscar intersección con cilindros
    while (current_cylinder)
    {
        if (ft_ray_cylinder_intersection(ray_origin, ray_dir, current_cylinder, &closestt, &rgb, &origin, &normal))
            found = 2;
        current_cylinder = current_cylinder->next;
    }

    // Buscar intersección con esferas
    while (current_sphere)
    {
        if (ft_ray_sphere_intersection(ray_origin, ray_dir, current_sphere, &closestt, &rgb, &origin))
            found = 1;
        current_sphere = current_sphere->next;
    }

	while (current_plane)
	{
		if (ft_ray_plane_intersection(ray_origin, ray_dir, current_plane, &closestt, &rgb, &origin, &normal))
			found = 3;
		current_plane = current_plane->next;
	}
	

    // Si no se encontró ninguna intersección, retornar negro
    if (found == 0)
        return ft_float_to_vec3(0.0f);

    // Calcular el punto de intersección más cercano
    hit_point = ft_dotv3(origin, ft_dotv3(ray_dir, ft_float_to_vec3(closestt), ft_multiply), ft_add);
	if (found == 1)
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
