/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:28:37 by descamil          #+#    #+#             */
/*   Updated: 2025/01/24 11:57:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int ft_ray_cylinder_intersection_x(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
    t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
    float a = ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
    float b = 2.0f * (ray_dir.y * to_cyl.y + ray_dir.z * to_cyl.z);
    float c = to_cyl.y * to_cyl.y + to_cyl.z * to_cyl.z - cylinder->radius * cylinder->radius;
    float disc = b * b - 4.0f * a * c;
    int intersect_with_body = 0;
    int intersect_with_left = 0;
    int intersect_with_right = 0;

    // Intersección con el cuerpo del cilindro
    if (disc >= 0.0f)
    {
        float t = (-b - sqrt(disc)) / (2.0f * a);
        if (t < *closest_t && t > 0.0f)
        {
            float x_intersection = to_cyl.x + t * ray_dir.x;
            float xmin = -cylinder->height / 2.0f;
            float xmax = cylinder->height / 2.0f;
            if (x_intersection > xmin && x_intersection < xmax)
            {
                *closest_t = t;
                *origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t), ft_multiply), ft_add);
                *rgb = cylinder->color;
                intersect_with_body = 1;

                // Calculate normal for cylinder body
                t_vec3 hit_point = *origin;
                t_vec3 axis = ft_create_vec3(1, 0, 0); // Cylinder is now aligned with X-axis
                t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
                t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
                *normal = ft_normalice(projection);
            }
        }
    }

    // Intersección con la tapa izquierda
    if (fabs(ray_dir.x) > 1e-6) // Evitar división por cero
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
                *origin = hit_point;
                *rgb = cylinder->color;
                intersect_with_left = 1;
                *normal = ft_create_vec3(-1, 0, 0); // Normal for left cap
            }
        }

        // Intersección con la tapa derecha
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
                *rgb = cylinder->color;
                intersect_with_right = 1;
                *normal = ft_create_vec3(1, 0, 0); // Normal for right cap
            }
        }
    }
    
    return intersect_with_body || intersect_with_left || intersect_with_right;
}

int ft_ray_cylinder_intersection_y(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
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

                // Calculate normal for cylinder body
                t_vec3 hit_point = *origin;
                t_vec3 axis = ft_create_vec3(0, 1, 0); // Assuming cylinder is aligned with Y-axis
                t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
                t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
                *normal = ft_normalice(projection);
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
                *normal = ft_create_vec3(0, -1, 0); // Normal for bottom cap
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
                *normal = ft_create_vec3(0, 1, 0); // Normal for top cap
            }
        }
    }
	
    return intersect_with_body || intersect_with_bottom || intersect_with_top;
}


int ft_ray_cylinder_intersection_z(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal)
{
    t_vec3 to_cyl = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
    float a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
    float b = 2.0f * (ray_dir.x * to_cyl.x + ray_dir.y * to_cyl.y);
    float c = to_cyl.x * to_cyl.x + to_cyl.y * to_cyl.y - cylinder->radius * cylinder->radius;
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
            float z_intersection = to_cyl.z + t * ray_dir.z;
            float zmin = -cylinder->height / 2.0f;
            float zmax = cylinder->height / 2.0f;
            if (z_intersection > zmin && z_intersection < zmax)
            {
                *closest_t = t;
                *origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(t), ft_multiply), ft_add);
                *rgb = cylinder->color;
                intersect_with_body = 1;

                // Calculate normal for cylinder body
                t_vec3 hit_point = *origin;
                t_vec3 axis = ft_create_vec3(0, 0, 1); // Cylinder is aligned with Z-axis
                t_vec3 to_hit = ft_dotv3(hit_point, cylinder->position, ft_subtract);
                t_vec3 projection = ft_dotv3(to_hit, ft_dotv3(axis, ft_float_to_vec3(ft_dot(to_hit, axis)), ft_multiply), ft_subtract);
                *normal = ft_normalice(projection);
            }
        }
    }

    // Intersección con la tapa inferior
    if (fabs(ray_dir.z) > 1e-6) // Evitar división por cero
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
                *rgb = cylinder->color;
                intersect_with_bottom = 1;
                *normal = ft_create_vec3(0, 0, -1); // Normal for bottom cap
            }
        }

        // Intersección con la tapa superior
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
                *rgb = cylinder->color;
                intersect_with_top = 1;
                *normal = ft_create_vec3(0, 0, 1); // Normal for top cap
            }
        }
    }
    return intersect_with_body || intersect_with_bottom || intersect_with_top;
}
