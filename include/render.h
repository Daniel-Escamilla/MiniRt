/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:21:49 by descamil          #+#    #+#             */
/*   Updated: 2025/01/24 11:59:30 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../minirt.h"

// ft_render.c
void	ft_create_render(t_mlx *data, t_image *image);
t_vec3	ft_create_vec3(float a, float b, float c);
t_vec3	ft_float_to_vec3(float a);

// ft_dotv3.c
float	ft_add(float a, float b);
float	ft_subtract(float a, float b);
float	ft_multiply(float a, float b);
float	ft_divide(float a, float b);
t_vec3	ft_dotv3(t_vec3 a, t_vec3 b, float (*op)(float, float));

// ft_maths.c
t_vec3  ft_clamp(t_vec3 color);
float   ft_max(float a, float b);
t_vec3  ft_normalice(t_vec3 vec);
t_vec3  ft_float_to_vec3(float a);
float	ft_dot(t_vec3 a, t_vec3 b);
t_vec3  ft_create_vec3(float a, float b, float c);

// ft_cylinder.c
int ft_ray_cylinder_intersection_x(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal);
int ft_ray_cylinder_intersection_y(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal);
int ft_ray_cylinder_intersection_z(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, float *closest_t, t_vec3 *rgb, t_vec3 *origin, t_vec3 *normal);

#endif
