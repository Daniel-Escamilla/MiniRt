/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:28:37 by descamil          #+#    #+#             */
/*   Updated: 2025/01/31 19:01:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int ft_ray_cylinder_intersection_x(t_image *image, t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
	t_cuadratic values;
	t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);


	
	values.a = ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	values.b = 2.0f * (ray_dir.y * to_cyl.y + ray_dir.z * to_cyl.z);
	values.c = to_cyl.y * to_cyl.y + to_cyl.z * to_cyl.z - cylinder->radius * cylinder->radius;
	values.disc = values.b * values.b - 4.0f * values.a * values.c;



	int intersect_with_body = 0;
	int intersect_with_left = 0;
	int intersect_with_right = 0;

	if (values.disc >= 0.0f)
	{
		values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
		if (values.tt < *closest_t && values.tt > 0.0f)
		{
			float x_intersection = to_cyl.x + values.tt * ray_dir.x;
			float xmin = -cylinder->height / 2.0f;
			float xmax = cylinder->height / 2.0f;
			if (x_intersection > xmin && x_intersection < xmax)
			{
				*closest_t = values.tt;
				*origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(values.tt), ft_multiply), ft_add);
				// *rgb = cylinder->color;
				intersect_with_body = 1;

				t_vec3 hit_point = *origin;
				t_vec3 axis = ft_create_vec3(1, 0, 0);
				t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, hit_point, cylinder->color, rgb);
				(void) shadow;
				t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
				*normal = ft_normalice(projection);
			}
		}
	}

	if (fabs(ray_dir.x) > 1e-6)
	{
		float t_left = (cylinder->position.x - cylinder->height / 2.0f - ray_origin.x) / ray_dir.x;
		if (t_left > 0.0f && t_left < *closest_t)
		{
			t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_left), ft_multiply), ft_add);
			if ((hit_point.y - cylinder->position.y) * (hit_point.y - cylinder->position.y) +
				(hit_point.z - cylinder->position.z) * (hit_point.z - cylinder->position.z) <= cylinder->radius * cylinder->radius)
			{
				*closest_t = t_left;
				hit_point.x = cylinder->position.x - cylinder->height / 2.0f;
				// *rgb = cylinder->color;
				*origin = hit_point;
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				(void) shadow;
				intersect_with_left = 1;
				*normal = ft_create_vec3(-1, 0, 0);
			}
		}

		float t_right = (cylinder->position.x + cylinder->height / 2.0f - ray_origin.x) / ray_dir.x;
		if (t_right > 0.0f && t_right < *closest_t)
		{
			t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_right), ft_multiply), ft_add);
			if ((hit_point.y - cylinder->position.y) * (hit_point.y - cylinder->position.y) +
				(hit_point.z - cylinder->position.z) * (hit_point.z - cylinder->position.z) <= cylinder->radius * cylinder->radius)
			{
				*closest_t = t_right;
				hit_point.x = cylinder->position.x + cylinder->height / 2.0f;
				*origin = hit_point;
				// *rgb = cylinder->color;
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				(void) shadow;
				intersect_with_right = 1;
				*normal = ft_create_vec3(1, 0, 0);
			}
		}
	}
	
	return intersect_with_body || intersect_with_left || intersect_with_right;
}

int ft_ray_cylinder_intersection_y(t_image *image, t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
	t_cuadratic values;
	t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
	values.a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
	values.b = 2.0f * (ray_dir.x * to_cyl.x + ray_dir.z * to_cyl.z);
	values.c = to_cyl.x * to_cyl.x + to_cyl.z * to_cyl.z - cylinder->radius * cylinder->radius;
	values.disc = values.b * values.b - 4.0f * values.a * values.c;
	int intersect_with_body = 0;
	int intersect_with_bottom = 0;
	int intersect_with_top = 0;

	if (values.disc >= 0.0f)
	{
		values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
		if (values.tt < *closest_t && values.tt > 0.0f)
		{
			float y_intersection = to_cyl.y + values.tt * ray_dir.y;
			float ymin = -cylinder->height / 2.0f;
			float ymax = cylinder->height / 2.0f;
			if (y_intersection > ymin && y_intersection < ymax)
			{
				*closest_t = values.tt;
				*origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(values.tt), ft_multiply), ft_add);
				// *rgb = cylinder->color;
				intersect_with_body = 1;

				t_vec3 hit_point = *origin;
				t_vec3 axis = ft_create_vec3(0, 1, 0);
				t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, hit_point, cylinder->color, rgb);
				(void) shadow;
				t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
				*normal = ft_normalice(projection);
			}
		}
	}

	if (fabs(ray_dir.y) > 1e-6)
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
				// *rgb = cylinder->color;
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				(void) shadow;
				intersect_with_bottom = 1;
				*normal = ft_create_vec3(0, -1, 0);
			}
		}

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
				// *rgb = cylinder->color;
				int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				(void) shadow;
				intersect_with_top = 1;
				*normal = ft_create_vec3(0, 1, 0);
			}
		}
	}
	
	return intersect_with_body || intersect_with_bottom || intersect_with_top;
}

int ft_ray_cylinder_intersection_z(t_image *image, t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
	t_cuadratic values;
	t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
	values.a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	values.b = 2.0f * (ray_dir.x * to_cyl.x + ray_dir.y * to_cyl.y);
	values.c = to_cyl.x * to_cyl.x + to_cyl.y * to_cyl.y - cylinder->radius * cylinder->radius;
	values.disc = values.b * values.b - 4.0f * values.a * values.c;
	int intersect_with_body = 0;
	int intersect_with_bottom = 0;
	int intersect_with_top = 0;

	if (values.disc >= 0.0f)
	{
		values.tt = (-values.b - sqrt(values.disc)) / (2.0f * values.a);
		if (values.tt < *closest_t && values.tt > 0.0f)
		{
			float z_intersection = to_cyl.z + values.tt * ray_dir.z;
			float zmin = -cylinder->height / 2.0f;
			float zmax = cylinder->height / 2.0f;
			if (z_intersection > zmin && z_intersection < zmax)
			{
				*closest_t = values.tt;
				*origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(values.tt), ft_multiply), ft_add);
				
				// *rgb = cylinder->color;
				intersect_with_body = 1;

				t_vec3 hit_point = *origin;
				t_vec3 axis = ft_create_vec3(0, 0, 1);
				t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
				// int	shadow = ft_shadow_sphere(image, image->color->light_dir, hit_point, cylinder->color, rgb);
				// (void) shadow;
				t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
				*normal = ft_normalice(projection);
			}
		}
	}

	if (fabs(ray_dir.z) > 1e-6)
	{
		float t_bottom = (cylinder->position.z - cylinder->height / 2.0f - ray_origin.z) / ray_dir.z;
		if (t_bottom > 0.0f && t_bottom < *closest_t)
		{
			t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_bottom), ft_multiply), ft_add);
			if ((hit_point.x - cylinder->position.x) * (hit_point.x - cylinder->position.x) +
				(hit_point.y - cylinder->position.y) * (hit_point.y - cylinder->position.y) <= cylinder->radius * cylinder->radius)
			{
				*closest_t = t_bottom;
				hit_point.z = cylinder->position.z - cylinder->height / 2.0f;
				*origin = hit_point;
				// *rgb = cylinder->color;
				// int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				// (void) shadow;
				intersect_with_bottom = 1;
				*normal = ft_create_vec3(0, 0, -1);
			}
		}

		float t_top = (cylinder->position.z + cylinder->height / 2.0f - ray_origin.z) / ray_dir.z;
		if (t_top > 0.0f && t_top < *closest_t)
		{
			t_vec3 hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t_top), ft_multiply), ft_add);
			if ((hit_point.x - cylinder->position.x) * (hit_point.x - cylinder->position.x) +
				(hit_point.y - cylinder->position.y) * (hit_point.y - cylinder->position.y) <= cylinder->radius * cylinder->radius)
			{
				*closest_t = t_top;
				hit_point.z = cylinder->position.z + cylinder->height / 2.0f;
				*origin = hit_point;
				// *rgb = cylinder->color;
				// int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
				// (void) shadow;
				intersect_with_top = 1;
				*normal = ft_create_vec3(0, 0, 1);
			}
		}
		if (intersect_with_body || intersect_with_bottom || intersect_with_top)
		{
			int	shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cylinder->color, rgb);
			(void) shadow;
		}
	}
	return intersect_with_body || intersect_with_bottom || intersect_with_top;
}
