/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:18:01 by descamil          #+#    #+#             */
/*   Updated: 2024/10/26 23:25:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_initialize(t_image *image)
{
	image->data = ft_calloc(sizeof(t_mlx), 1);
	image->circle = ft_calloc(sizeof(t_circle), 1);
	image->color = ft_calloc(sizeof(t_color), 1);
	image->light = ft_calloc(sizeof(t_light), 1);
	image->camera = ft_calloc(sizeof(t_camera), 1);
	image->keys = ft_calloc(sizeof(t_keys), 1);
	
	image->width = 810;
	image->height = 540;
	
	image->color->plus = 1;

	image->camera->position.x = 0.0f;
	image->camera->position.y = 0.0f;
	image->camera->position.z = 2.0f;

	image->color->rgb.x = 1.0f;
	image->color->rgb.y = 0.0f;
	image->color->rgb.z = 1.0f;
	
	image->circle->radius = 0.5f;

	image->color->light_dir.x = -1.0f;
	image->color->light_dir.y = -1.0f;
	image->color->light_dir.z = -1.0f;

	image->aspect_ratio = (float)image->width / (float)image->height;
}
