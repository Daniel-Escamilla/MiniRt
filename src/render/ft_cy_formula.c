/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_formula.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:40:46 by descamil          #+#    #+#             */
/*   Updated: 2025/01/31 22:17:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	ft_init_ray_origin(t_cy_formula *values, t_vec3 ray_origin, int type)
{
	if (type == 'X')
		(*values).ray_origin.v1 = ray_origin.x;
	if (type == 'Y')
		(*values).ray_origin.v1 = ray_origin.y;
	if (type == 'Z')
		(*values).ray_origin.v1 = ray_origin.z;
}

void	ft_init_global(t_cy_formula *values, t_vec3 generic, int type, char *str)
{
	t_vec3	*tmp;

	if (ft_strncmp(str, "CYL", 3) == 0)
		tmp = &(*values).to_cyl;
	else if (ft_strncmp(str, "POS", 3) == 0)
		tmp = &(*values).cy_pos;
	else if (ft_strncmp(str, "HIT", 3) == 0)
		tmp = &(*values).hit_point;
	else if (ft_strncmp(str, "DIR", 3) == 0)
		tmp = &(*values).ray_dir;
	(*tmp).v1 = generic.x;
	(*tmp).v2 = generic.z;
	(*tmp).v3 = generic.y;
	if (type == 'X')
	{
		(*tmp).v1 = generic.y;
		(*tmp).v3 = generic.x;
	}
	if (type == 'Z')
	{
		(*tmp).v2 = generic.y;
		(*tmp).v3 = generic.z;
	}
}

void	ft_init_axis(t_cy_formula *values, int type)
{
	if (type == 'X')
		(*values).axis = ft_create_vec3(1, 0, 0);
	if (type == 'Y')
		(*values).axis = ft_create_vec3(0, 1, 0);
	if (type == 'Z')
		(*values).axis = ft_create_vec3(0, 0, 1);
}

void	ft_neg_axis(t_cy_formula *values, int type)
{
	if (type == 'X')
		(*values).axis = ft_create_vec3(-1, 0, 0);
	if (type == 'Y')
		(*values).axis = ft_create_vec3(0, -1, 0);
	if (type == 'Z')
		(*values).axis = ft_create_vec3(0, 0, -1);
}

t_cy_formula	ft_init_cy(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, int type)
{
	t_cy_formula	values;
	t_vec3			tmp;

	tmp = ft_dotv3(ray_origin, cylinder->position, ft_subtract);
	ft_init_ray_origin(&values, ray_origin, type);
	ft_init_global(&values, tmp, type, "CYL");
	ft_init_global(&values, cylinder->position, type, "POS");
	ft_init_global(&values, ray_dir, type, "DIR");
	ft_init_axis(&values, type);
	values.inter = 0;
	return (values);
}

// t_vec3 hit_point= ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(// T CORRESPONDIENTE //), ft_multiply), ft_add);
// ft_init_global(&values, hit_point, type, "HIT");

// void	ft_rest_values(t_vec3 *ray, int type)
// {
// 	float	tmp;

// 	if (type != 'Z')
// 	{
// 		tmp = (*ray).v2;
// 		(*ray).v2 = (*ray).v3;
// 		(*ray).v3 = tmp;
// 	}
// 	if (type == 'X')
// 	{
// 		tmp = (*ray).v1;
// 		(*ray).v1 = (*ray).v3;
// 		(*ray).v3 = tmp;
// 	}
// 		// tmp = (*ray).v2;
// 		// (*ray).v2 = (*ray).v3;
// 		// (*ray).v3 = tmp;
// }

int	ft_cylinder_formula(t_image *image, t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cy, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal, int type)
{
	t_cy_formula	v;
	t_cuadratic		cuadratic;
	t_vec3			hit_point;

// BIEN //

	v = ft_init_cy(ray_origin, ray_dir, cy, type);
	cuadratic.a = v.ray_dir.v1 * v.ray_dir.v1 + v.ray_dir.v2 * v.ray_dir.v2;
	cuadratic.b = 2.0f * (v.ray_dir.v1 * v.to_cyl.v1 + v.ray_dir.v2 * v.to_cyl.v2);
	cuadratic.c = v.to_cyl.v1 * v.to_cyl.v1 + v.to_cyl.v2 * v.to_cyl.v2 - cy->radius * cy->radius;
	cuadratic.disc = cuadratic.b * cuadratic.b - 4.0f * cuadratic.a * cuadratic.c;

// BIEN //

	if (cuadratic.disc >= 0.0f)
	{
		cuadratic.tt = (-cuadratic.b - sqrt(cuadratic.disc)) / (2.0f * cuadratic.a);
		if (cuadratic.tt < *closest_t && cuadratic.tt > 0.0f)
		{
			v.intersection = v.to_cyl.v3 + cuadratic.tt * v.ray_dir.v3;
			float min = -cy->height / 2.0f;
			float max = cy->height / 2.0f;
			if (v.intersection > min && v.intersection < max)
			{
				*closest_t = cuadratic.tt;
				*origin = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(cuadratic.tt), ft_multiply), ft_add);
				
				v.inter = 1;
				
				hit_point = *origin;
				// v.axis = ft_create_vec3(1, 0, 0);
				v.to_hit = ft_dotv3(hit_point, cy->position, ft_subtract);
				v.shadow = ft_shadow_sphere(image, image->color->light_dir, hit_point, cy->color, rgb);
				v.projection = ft_dotv3(v.to_hit, ft_dotv3(v.axis, ft_float_to_vec3(ft_dot(v.to_hit, v.axis)), ft_multiply), ft_subtract);
				*normal = ft_normalice(v.projection);
				float d = ft_max(ft_dot(*normal, image->color->light_dir), 0.0f);
				if (d < 0.00f)
					printf("aja\n");
			}
		}
	}
	if (fabs(v.ray_dir.v3) > 1e-6)
	{
		float	tap;
		v.tt.tap1 = (v.cy_pos.v3 - cy->height / 2.0f - v.ray_origin.v1) / v.ray_dir.v3;
		v.tt.tap2 = (v.cy_pos.v3 + cy->height / 2.0f - v.ray_origin.v1) / v.ray_dir.v3;
		tap = v.tt.tap1;
		if (tap > v.tt.tap2)
			tap = v.tt.tap2;
		if (tap > 0.0f && tap < *closest_t)
		{
			hit_point = ft_dotv3(ray_origin, ft_dotv3(ray_dir, ft_float_to_vec3(tap), ft_multiply), ft_add);
			ft_init_global(&v, hit_point, type, "HIT");
			if ((v.hit_point.v1 - v.cy_pos.v1) * (v.hit_point.v1 - v.cy_pos.v1) +
				(v.hit_point.v2 - v.cy_pos.v2) * (v.hit_point.v2 - v.cy_pos.v2) <= cy->radius * cy->radius)
			{
				*closest_t = tap;
				if (tap == v.tt.tap1)
					ft_neg_axis(&v, type);
				*origin = hit_point;
				v.shadow = ft_shadow_sphere(image, image->color->light_dir, *origin, cy->color, rgb);
				v.inter = 1;
				printf("X = %f\n", v.axis.x);
				printf("Y = %f\n", v.axis.y);
				printf("Z = %f\n", v.axis.z);
				*normal = v.axis;
			}
		}
	}
	return (v.inter);
}