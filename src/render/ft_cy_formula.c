/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_formula.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:40:46 by descamil          #+#    #+#             */
/*   Updated: 2025/02/16 16:47:46 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

typedef struct s_local_coords
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}			t_local_coords;

t_local_coords ft_create_local_coords(t_vec3 axis)
{
	t_local_coords	local;
	t_vec3			up;
	
	local.w = ft_normalice(axis);
	up = (t_vec3){{0, 1, 0}};
	if (fabs(ft_dot(local.w, up)) > 0.9999f)
		up = (t_vec3){{1, 0, 0}};
	local.u = ft_normalice(ft_cross(up, local.w));
	local.v = ft_cross(local.w, local.u);
	return (local);
}

t_vec3 ft_world_to_local(t_vec3 p, t_vec3 origin, t_local_coords local)
{
	t_vec3	tmp;
	t_vec3	result;

	tmp = ft_dotv3(p, origin, ft_subtract);
	result.x = ft_dot(tmp, local.u);
	result.y = ft_dot(tmp, local.v);
	result.z = ft_dot(tmp, local.w);
	return (result);
}

t_vec3 ft_local_to_world(t_vec3 p, t_vec3 origin, t_local_coords local)
{
	t_vec3 result;
	
	result.x = origin.x + p.x * local.u.x + p.y * local.v.x + p.z * local.w.x;
	result.y = origin.y + p.x * local.u.y + p.y * local.v.y + p.z * local.w.y;
	result.z = origin.z + p.x * local.u.z + p.y * local.v.z + p.z * local.w.z;
	return (result);
}

// int ft_cylinder_formula(t_ray_values *r, t_vec3 *rgb, t_vec3 *normal)
// {
// 	t_cuadratic cuadratic;

// 	t_local_coords local = ft_create_local_coords(r->current_objects->cylinder->normal);
// 	t_vec3 local_origin = ft_world_to_local(r->ray_origin, r->current_objects->cylinder->position, local);
// 	t_vec3 local_dir = ft_world_to_local(r->ray_dir, (t_vec3){{0,0,0}}, local);

// 	cuadratic.a = local_dir.x * local_dir.x + local_dir.y * local_dir.y;
// 	cuadratic.b = 2 * (local_origin.x * local_dir.x + local_origin.y * local_dir.y);
// 	cuadratic.c = local_origin.x * local_origin.x + local_origin.y * local_origin.y - r->current_objects->cylinder->radius * r->current_objects->cylinder->radius;

// 	cuadratic.disc = cuadratic.b * cuadratic.b - 4 * cuadratic.a * cuadratic.c;
// 	if (cuadratic.disc < 0)
// 		return (0);

// 	float t1 = (-cuadratic.b - sqrt(cuadratic.disc)) / (2 * cuadratic.a);
// 	float t2 = (-cuadratic.b + sqrt(cuadratic.disc)) / (2 * cuadratic.a);

// 	cuadratic.tt = t1;
// 	if (t2 < t1)
// 		cuadratic.tt = t2;
// 	if (cuadratic.tt < 0)
// 		return (0);

// 	t_vec3 local_hit = ft_create_vec3(local_origin.x + cuadratic.tt * local_dir.x, local_origin.y + cuadratic.tt * local_dir.y, local_origin.z + cuadratic.tt * local_dir.z);

// 	if (fabs(local_hit.z) > r->current_objects->cylinder->height / 2) {
// 		cuadratic.tt = (r->current_objects->cylinder->height / 2 - local_origin.z) / local_dir.z;
// 		local_hit = ft_create_vec3(local_origin.x + cuadratic.tt * local_dir.x, local_origin.y + cuadratic.tt * local_dir.y, r->current_objects->cylinder->height / 2);
// 		if (local_hit.x * local_hit.x + local_hit.y * local_hit.y > r->current_objects->cylinder->radius * r->current_objects->cylinder->radius) {
// 			cuadratic.tt = (-r->current_objects->cylinder->height / 2 - local_origin.z) / local_dir.z;
// 			local_hit = ft_create_vec3(local_origin.x + cuadratic.tt * local_dir.x, local_origin.y + cuadratic.tt * local_dir.y, -r->current_objects->cylinder->height / 2);
// 			if (local_hit.x * local_hit.x + local_hit.y * local_hit.y > r->current_objects->cylinder->radius * r->current_objects->cylinder->radius) {
// 				return 0;
// 			}
// 		}
// 	}
// 	*r->origin = ft_local_to_world(local_hit, r->current_objects->cylinder->position, local);
// 	*r->tt = cuadratic.tt;
// 	if (fabs(local_hit.z) == r->current_objects->cylinder->height / 2)
// 		*normal = ft_local_to_world((t_vec3){{0, 0, local_hit.z > 0 ? 1 : -1}}, (t_vec3){{0,0,0}}, local);
// 	else
// 		*normal = ft_local_to_world((t_vec3){{local_hit.x, local_hit.y, 0}}, (t_vec3){{0,0,0}}, local);
// 	*normal = ft_normalice(*normal);
// 	t_vec3 light_dir = ft_normalice(ft_dotv3(r->current_image->color->light_dir, *r->origin, ft_subtract));
// 	float epsilon = 0.001f;
// 	t_vec3 shadow_origin = ft_dotv3(*r->origin, ft_dotv3(*normal, ft_float_to_vec3(epsilon), ft_multiply), ft_add);
// 	ft_shadow_sphere(r->current_image, light_dir, shadow_origin, r->current_objects->cylinder->color, rgb);
// 	return (1);
// }


int ft_cylinder_formula(t_ray_values *r, t_vec3 *rgb, t_vec3 *normal)
{
    t_cuadratic cuadratic;
    float closest_t = *r->tt;

    t_local_coords local = ft_create_local_coords(r->current_objects->cylinder->normal);
    t_vec3 local_origin = ft_world_to_local(r->ray_origin, r->current_objects->cylinder->position, local);
    t_vec3 local_dir = ft_world_to_local(r->ray_dir, (t_vec3){{0,0,0}}, local);

    cuadratic.a = local_dir.x * local_dir.x + local_dir.y * local_dir.y;
    cuadratic.b = 2 * (local_origin.x * local_dir.x + local_origin.y * local_dir.y);
    cuadratic.c = local_origin.x * local_origin.x + local_origin.y * local_origin.y - r->current_objects->cylinder->radius * r->current_objects->cylinder->radius;
    cuadratic.disc = cuadratic.b * cuadratic.b - 4 * cuadratic.a * cuadratic.c;
    if (cuadratic.disc < 0)
        return (0);
    float t1 = (-cuadratic.b - sqrt(cuadratic.disc)) / (2 * cuadratic.a);
    float t2 = (-cuadratic.b + sqrt(cuadratic.disc)) / (2 * cuadratic.a);
    cuadratic.tt = (t1 < t2 && t1 > 0) ? t1 : t2;
    if (cuadratic.tt <= 0 || cuadratic.tt >= closest_t)
        return (0);
    t_vec3 local_hit = ft_create_vec3(local_origin.x + cuadratic.tt * local_dir.x, 
                                      local_origin.y + cuadratic.tt * local_dir.y, 
                                      local_origin.z + cuadratic.tt * local_dir.z);
    if (fabs(local_hit.z) > r->current_objects->cylinder->height / 2) {
        float t_cap = (r->current_objects->cylinder->height / 2 - local_origin.z) / local_dir.z;
        if (t_cap <= 0 || t_cap >= closest_t)
            return (0);
        
        local_hit = ft_create_vec3(local_origin.x + t_cap * local_dir.x, 
                                   local_origin.y + t_cap * local_dir.y, 
                                   r->current_objects->cylinder->height / 2);
        
        if (local_hit.x * local_hit.x + local_hit.y * local_hit.y > r->current_objects->cylinder->radius * r->current_objects->cylinder->radius) {
            t_cap = (-r->current_objects->cylinder->height / 2 - local_origin.z) / local_dir.z;
            if (t_cap <= 0 || t_cap >= closest_t)
                return (0);
            
            local_hit = ft_create_vec3(local_origin.x + t_cap * local_dir.x, 
                                       local_origin.y + t_cap * local_dir.y, 
                                       -r->current_objects->cylinder->height / 2);
            
            if (local_hit.x * local_hit.x + local_hit.y * local_hit.y > r->current_objects->cylinder->radius * r->current_objects->cylinder->radius) {
                return 0;
            }
        }
        cuadratic.tt = t_cap;
    }
    *r->origin = ft_local_to_world(local_hit, r->current_objects->cylinder->position, local);
    *r->tt = cuadratic.tt;
    if (fabs(local_hit.z) == r->current_objects->cylinder->height / 2)
        *normal = ft_local_to_world((t_vec3){{0, 0, local_hit.z > 0 ? 1 : -1}}, (t_vec3){{0,0,0}}, local);
    else
        *normal = ft_local_to_world((t_vec3){{local_hit.x, local_hit.y, 0}}, (t_vec3){{0,0,0}}, local);
    *normal = ft_normalice(*normal);
    t_vec3 light_dir = ft_normalice(ft_dotv3(r->current_image->color->light_dir, *r->origin, ft_subtract));
    float epsilon = 0.001f;
    t_vec3 shadow_origin = ft_dotv3(*r->origin, ft_dotv3(*normal, ft_float_to_vec3(epsilon), ft_multiply), ft_add);
    ft_shadow_sphere(r->current_image, light_dir, shadow_origin, r->current_objects->cylinder->color, rgb);
    return (1);
}
