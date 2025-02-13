/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:45:27 by descamil          #+#    #+#             */
/*   Updated: 2025/02/13 18:31:48 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_initialize(t_image *image)
{
	image->data = ft_calloc(sizeof(t_mlx), 1);
	image->sphere = ft_calloc(sizeof(t_sphere), 1);
	image->cylinder = ft_calloc(sizeof(t_cylinder), 1);
	image->color = ft_calloc(sizeof(t_color), 1);
	image->light = ft_calloc(sizeof(t_light), 1);
	image->camera = ft_calloc(sizeof(t_camera), 1);
	image->keys = ft_calloc(sizeof(t_keys), 1);
	image->plane = ft_calloc(sizeof(t_plane), 1);
	image->ambient = ft_calloc(sizeof(t_ambient), 1);
	
	image->width = 600;
	image->height = 600;
	
	image->color->plus = 1;

	image->color->rgb.x = 1.0f;
	image->color->rgb.y = 0.0f;
	image->color->rgb.z = 1.0f;
	
	image->ambient->ratio = 0.5;
	image->ambient->rgb = ft_create_vec3(1.0f, 0.0f, 0.0f);

	image->cylinder->position = ft_create_vec3(2.0f, 0.0f, 0.0f);
	image->cylinder->radius = 1.0f;
	image->cylinder->height = 3.0f;
	image->cylinder->normal = ft_create_vec3(0.5f, 0.7f, -0.5f);
	image->cylinder->color = ft_create_vec3(0.741f, 0.557f, 0.376f);

	image->plane->position = ft_create_vec3(1.0f, -5.0f, 2.0f);
	image->plane->normal = ft_create_vec3(0.0f, 1.0f, 0.0f);
	image->plane->color = ft_create_vec3(0.0f, 0.0f, 1.0f);

	image->plane->next = ft_calloc(sizeof(t_plane), 1);
	image->plane->next->position = ft_create_vec3(1.0f, 0.0f, -15.0f);
	image->plane->next->normal = ft_create_vec3(0.0f, 0.0f, 1.0f);
	image->plane->next->color = ft_create_vec3(1.0f, 0.0, 0.0f);
	
	image->plane->next->next = ft_calloc(sizeof(t_plane), 1);
	image->plane->next->next->position = ft_create_vec3(-15.0f, 0.0f, 2.0f);
	image->plane->next->next->normal = ft_create_vec3(1.0f, 0.0f, 0.0f);
	image->plane->next->next->color = ft_create_vec3(0.0f, 1.0, 0.0f);

	image->color->light_dir.x = 0.0f;
	image->color->light_dir.y = -6.0f;
	image->color->light_dir.z = 0.0f;

	image->aspect_ratio = (float)image->width / (float)image->height;
}
