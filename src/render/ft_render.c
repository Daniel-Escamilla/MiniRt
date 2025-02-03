/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2025/02/03 19:33:29 by descamil         ###   ########.fr       */
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

float ft_length(t_vec3 v)
{
    return sqrtf(ft_dot(v, v));
}

// ( bx² ​+ by² ​+ bz² ​)t² + 2(ax​bx ​+ ay​by ​+ az​bz​)t + (ax²​ + ay² + az² − r²) = 0
// a = ray_direction
// b = ray_origin
// r = radius
// t = hit distant

// b² - 4.0f * a * c;
// (-b +- sqrt(discriminant)) / 2a

// radius = 0.5f;
	
// t_vec3 test = ft_dotv3([El punto de golpeo de la esfera(que no se cual es, en vec3)], sphere->position[esto sera solo para las esferas], ft_subtract);
// float a = ft_dot([Vector de la posicion de la luz, sin normalizar], [Vector de la posicion de la luz, sin normalizar]);
// float b = 2.0f * ft_dot([Vector de la posicion de la luz, sin normalizar], test);
// float c = ft_dot(test, test) - sphere->radius[solo servirá para las esferas] * sphere->radius[solo servirá para las esferas];
// float disc = b * b - 4.0f * a * c;

int ft_shadow_sphere(t_image *image, t_vec3 light_dir, t_vec3 intersection_point, t_vec3 color, t_vec3 *rgb)
{
	t_cuadratic	values;
	t_sphere	*sphere;

	light_dir = ft_normalice(light_dir);
	light_dir = ft_dotv3(light_dir, ft_float_to_vec3(-1), ft_multiply);
	
	sphere = image->sphere;
	while (sphere != NULL)
	{
		values.test = ft_dotv3(intersection_point, sphere->position, ft_subtract);
		values.a = ft_dot(light_dir, light_dir);
		values.b = 2.0f * ft_dot(light_dir, values.test);
		values.c = ft_dot(values.test, values.test) - sphere->radius * sphere->radius;
		values.disc = values.b * values.b - 4.0f * values.a * values.c;

		if (values.disc > 0)
		{
			values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
			if (values.tt > 0.001f)
			{
				*rgb = ft_dotv3(color, ft_float_to_vec3(0.60f), ft_multiply);
				return (1);
			}
			values.tt = (-values.b + sqrt(values.disc)) / (2.0f * values.a);
			if (values.tt > 0.001f)
			{
				*rgb = ft_dotv3(color, ft_float_to_vec3(0.60f), ft_multiply);
				return (1);
			}
		}
		sphere = sphere->next;
	}
	*rgb = color;
	return (0);
}

// int ft_shadow_plane(t_image *image, int index, t_vec3 light_dir, t_vec3 intersection_point, t_vec3 color, t_vec3 *rgb)
// {
// 	t_plane *plane = &image->scene->planes[index];
// 	t_cuadratic values;

// 	// Vector desde el punto de intersección al plano
// 	values.test = ft_dotv3(intersection_point, plane->position, ft_subtract);

// 	// Calcular el denominador del plano (similar a la función de intersección del plano)
// 	float denom = ft_dot(plane->normal, light_dir);

// 	// Evitar división por cero
// 	if (fabs(denom) > 0.000001)
// 	{
// 		// Calcular t (distancia a la intersección)
// 		values.tt = ft_dot(values.test, plane->normal) / denom;

// 		// Comprobar si la intersección está entre el punto y la luz
// 		if (values.tt > 0.001f && values.tt < 1.0f)
// 		{
// 			// Está en sombra
// 			*rgb = ft_dotv3(color, ft_float_to_vec3(0.40f), ft_multiply);
// 			return 1;
// 		}
// 	}

// 	// No está en sombra
// 	*rgb = color;
// 	return 0;
// }


#define LIGHT_RADIUS 0.5f
#define LIGHT_COLOR (t_vec3){{1.0f, 1.0f, 1.0f}}

int ft_ray_light_intersection(t_image *image, t_ray_values *v, t_vec3 *rgb)
{
	t_cuadratic	values;

	t_vec3 pos = image->color->light_dir;

	values.test = ft_dotv3((*v).ray_origin, pos, ft_subtract);
	values.a = ft_dot((*v).ray_dir, (*v).ray_dir);
	values.b = 2.0f * ft_dot((*v).ray_dir, values.test);
	values.c = ft_dot(values.test, values.test) - LIGHT_RADIUS * LIGHT_RADIUS;
	values.disc = values.b * values.b - 4.0f * values.a * values.c;

	if (values.disc >= 0)
	{
		values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
		if (values.tt < *(*v).tt)
		{
			*(*v).tt = values.tt;
			*(*v).origin = values.test;
			*rgb = (*v).current_sp->color;
			return (1);
		}
	}
	return (0);
}



int ft_ray_sphere_intersection(t_ray_values *v, t_vec3 *rgb)
{
	t_cuadratic	values;
	int			shadow;

	values.test = ft_dotv3((*v).ray_origin, (*v).current_sp->position, ft_subtract);
	values.a = ft_dot((*v).ray_dir, (*v).ray_dir);
	values.b = 2.0f * ft_dot((*v).ray_dir, values.test);
	values.c = ft_dot(values.test, values.test) - (*v).current_sp->radius * (*v).current_sp->radius;
	values.disc = values.b * values.b - 4.0f * values.a * values.c;

	if (values.disc >= 0)
	{
		values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
		if (values.tt < *(*v).tt)
		{
			*(*v).tt = values.tt;
			*(*v).origin = values.test;
			*rgb = (*v).current_sp->color;
			t_vec3 intersection_point = ft_dotv3((*v).ray_origin, ft_dotv3((*v).ray_dir, ft_float_to_vec3(*(*v).tt), ft_multiply), ft_add);
			shadow = ft_shadow_sphere((*v).current_image, (*v).current_image->color->light_dir, intersection_point, (*v).current_sp->color, rgb);
			if (shadow == 1)
				return (1);
			return (1);
		}
	}
	return (0);
}

int	ft_ray_cylinder_intersection(t_ray_values *v, t_vec3 *rgb, t_vec3 *normal)
{
	if ((*v).current_cy->normal.x == 1 && (*v).current_cy->normal.y == 0 && (*v).current_cy->normal.z == 0)
		return (ft_cylinder_formula(v, rgb, normal,'X'));
	else if ((*v).current_cy->normal.x == 0 && (*v).current_cy->normal.y == 1 && (*v).current_cy->normal.z == 0)
		return (ft_cylinder_formula(v, rgb, normal, 'Y'));
	return (ft_cylinder_formula(v, rgb, normal, 'Z'));
}

t_vec3 ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}

float max_or_min(float value, float min, float max)
{
    if (value < min)
		return (min);
    if (value > max)
		return (max);
    return (value);
}

int ft_ray_plane_intersection(t_ray_values *v, t_vec3 *rgb, t_vec3 *normal)
{
    float denom;
    float t;
    t_vec3 p0l0;
    t_vec3 intersection;
    int shadow;
    float distance_to_light;
    float attenuation;
    const float k_c = 1.0f;  // Atenuación constante
    const float k_l = 0.1f;  // Atenuación lineal
    const float k_q = 0.01f; // Atenuación cuadrática

    denom = ft_dot((*v).current_pl->normal, (*v).ray_dir);
    
    if (fabs(denom) < 0.000001)
        return 0;

    p0l0 = ft_dotv3((*v).current_pl->position, (*v).ray_origin, ft_subtract);
    t = ft_dot(p0l0, (*v).current_pl->normal) / denom;

    if (t < 0 || t > *(*v).tt)
        return 0;

    intersection = ft_dotv3((*v).ray_origin, ft_dotv3((*v).ray_dir, ft_float_to_vec3(t), ft_multiply), ft_add);

    *(*v).tt = t;
    *(*v).origin = intersection;

    shadow = ft_shadow_sphere((*v).current_image, (*v).current_image->color->light_dir, intersection, (*v).current_pl->color, rgb);
    (void)shadow;

    // Calcular distancia a la fuente de luz
    distance_to_light = ft_length(ft_dotv3((*v).current_image->color->light_dir, intersection, ft_subtract));

    // Calcular atenuación en función de la distancia
    attenuation = 1.0f / (k_c + k_l * distance_to_light + k_q * distance_to_light * distance_to_light);

    float brightness = max_or_min(attenuation, 0.2f, 1.0f); // Limitar entre 20% y 100%

    // Aplicar atenuación y luz ambiental al color
    t_vec3 attenuated_color = ft_dotv3(*rgb, ft_float_to_vec3(brightness), ft_multiply);
    *rgb = attenuated_color;

    *normal = (*v).current_pl->normal;
    
    if (ft_dot(*normal, (*v).ray_dir) > 0)
        *normal = ft_dotv3(*normal, ft_float_to_vec3(-1), ft_multiply);

    return 1;
}

t_vec3 ft_calculate_lighting(t_vec3 normal, t_vec3 rgb, t_image *image, int found)
{
	t_vec3 directional_color;
	t_vec3 light_dir = ft_normalice(image->color->light_dir);
	light_dir = ft_dotv3(light_dir, ft_float_to_vec3(-1), ft_multiply);
	float d = ft_max(ft_dot(normal, light_dir), 0.0f);
	if (d < 0.1f && found != 1)
		d = 0.1f;
	directional_color = ft_dotv3(ft_dotv3(rgb, ft_float_to_vec3(d), ft_multiply), ft_float_to_vec3(0.1), ft_add);
	return ft_dotv3(directional_color, ft_float_to_vec3(1.0f), ft_multiply);
}

t_ray_values	ft_init_ray_values(t_image *image, t_vec2 coord)
{
	t_ray_values	values;

	// coord.x *= image->aspect_ratio;
	// values.ray_dir = ft_create_vec3(-1.0f, coord.y, coord.x);
	// values.ray_origin = ft_create_vec3(15.0f, 0.0f, 0.0f);
	values.ray_dir = ft_create_vec3(coord.x, coord.y, -1.0f);
	values.ray_origin = ft_create_vec3(0.0f, 0.0f, 10.f);
	values.tt = ft_calloc(sizeof(float), 1);
	*values.tt = FLT_MAX;// Inicializa la distancia más cercana
	values.found = 0;
	values.current_sp = image->sphere;
	values.current_cy = image->cylinder;
	values.current_pl = image->plane;
	values.current_image = image;
	values.origin = ft_calloc(sizeof(t_vec3), 1);
	*values.origin = ft_create_vec3(0, 0, 0);

	return (values);
}

t_vec3 ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_ray_values	v;
	t_vec3			hit_point;
	t_vec3			normal;
	t_vec3			rgb;
	float			tt;

	v = ft_init_ray_values(image, coord);
	if (ft_ray_light_intersection(image, &v, &rgb))
		tt = *v.tt;
	while (v.current_sp)
	{
		if (ft_ray_sphere_intersection(&v, &rgb))
			v.found = 1;
		v.current_sp = v.current_sp->next;
	}
	while (v.current_cy)
	{
		if (ft_ray_cylinder_intersection(&v, &rgb, &normal))
			v.found = 2;
		v.current_cy = v.current_cy->next;
	}
	while (v.current_pl)
	{
		if (ft_ray_plane_intersection(&v, &rgb, &normal))
			v.found = 3;
		v.current_pl = v.current_pl->next;
	}
	hit_point = ft_dotv3(*v.origin, ft_dotv3(v.ray_dir, ft_float_to_vec3(*v.tt), ft_multiply), ft_add);
	if (v.found == 1)
		normal = ft_normalice(hit_point);
	if (*v.tt == tt)
		return ((t_vec3){{1.0f, 1.0f, 1.0f}});
	if (v.found == 0)
		return ft_float_to_vec3(0.0f);
	free(v.tt);
	free(v.origin);
	return ft_calculate_lighting(normal, rgb, image, v.found);  // Calcular iluminación
}

# include <time.h>

// void	ft_create_render(t_mlx *data, t_image *image)
// {
// 	t_vec3	color;
// 	t_vec2	coord;
// 	int		y;
// 	int		x;

// 	clock_t start_time = clock();

// 	y = 0;
// 	while (y < image->height)
// 	{
// 		coord.y = ((float)y / (float)image->height) * -1 + 1;
// 		coord.y = coord.y * 2.0f - 1.0f;
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			coord.x = ((float)x / (float)image->width);
// 			coord.x = coord.x * 2.0f - 1.0f;
// 			color = ft_per_pixel(image, coord);
// 			color = ft_clamp(color);
// 			my_mlx_pixel_put(data, x, y, ft_convert_rgba(color));
// 			x++;
// 		}
// 		y++;
// 	}

// 	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
// 	clock_t end_time = clock();  // Finaliza la medición del tiempo
// 	double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // Calcula la duración en milisegundos
// 	printf("Tiempo de ejecución: %f ms\n", duration);  // Imprime el tiempo de ejecución
// }

typedef struct s_thread_data {
    t_mlx *data;      // Apunta a los datos de la estructura t_mlx (probablemente contiene la información de la ventana y el buffer de la imagen).
    t_image *image;   // Apunta a la estructura t_image (contiene información sobre la imagen que estamos renderizando, como el tamaño, el puntero al buffer de píxeles, etc.).
    int start_row;    // Fila inicial que este hilo debe procesar.
    int end_row;      // Fila final que este hilo debe procesar (sin incluirla).
} t_thread_data;

#include <pthread.h>

void *ft_render_chunk(void *arg)
{
    t_thread_data *thread_data = (t_thread_data *)arg;
    t_vec3 color;
    t_vec2 coord;
    int y;
    int x;

    for (y = thread_data->start_row; y < thread_data->end_row; y++) {
        coord.y = ((float)y / (float)thread_data->image->height) * -1 + 1;
        coord.y = coord.y * 2.0f - 1.0f;
        for (x = 0; x < thread_data->image->width; x++) {
            coord.x = ((float)x / (float)thread_data->image->width);
            coord.x = coord.x * 2.0f - 1.0f;
            color = ft_per_pixel(thread_data->image, coord);
            color = ft_clamp(color);
            my_mlx_pixel_put(thread_data->data, x, y, ft_convert_rgba(color));
        }
    }
    return NULL;
}

void ft_create_render(t_mlx *data, t_image *image) {
    // t_vec3 color;
    // t_vec2 coord;
    // int y;
    // int x;

    clock_t start_time = clock();

    int num_threads = 8;  // Número de hilos a usar
    pthread_t threads[num_threads];
    t_thread_data thread_data[num_threads];
    int rows_per_thread = image->height / num_threads;

    // Crear los hilos y asignarles un rango de filas
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].data = data;
        thread_data[i].image = image;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? image->height : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, ft_render_chunk, &thread_data[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);

    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    printf("Tiempo de ejecución: %f ms\n", duration);
}
