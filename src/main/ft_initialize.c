/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:18:01 by descamil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/03 19:32:44 by descamil         ###   ########.fr       */
=======
/*   Updated: 2025/02/05 10:38:30 by descamil         ###   ########.fr       */
>>>>>>> c5122ce (Inicio de Norminette)
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_select_type(t_vec3 normal)
{
	if (normal.x == 1)
		return ('X');
	if (normal.y == 1)
		return ('Y');
	if (normal.z == 1)
		return ('Z');
	return (0);
}

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
	
	image->ambient->ratio = 0.2;
	image->ambient->rgb = ft_create_vec3(1.0f, 0.0f, 0.0f);

	// image->sphere->position = ft_create_vec3(0.0f, 2.0f, 2.0f);
	// image->sphere->radius = 0.5f;
	// image->sphere->color = ft_create_vec3(1.0f, 1.0f, 1.0f);

	// image->sphere->next = ft_calloc(sizeof(t_sphere), 1);
	// image->sphere->next->position = ft_create_vec3(1.0f, -1.5f, 0.0f);
	// image->sphere->next->radius = 0.5f;
	// image->sphere->next->color = ft_create_vec3(0.0f, 1.0f, 0.0f);

<<<<<<< HEAD
	image->sphere->next->next = ft_calloc(sizeof(t_sphere), 1);
	image->sphere->next->next->position = ft_create_vec3(-1.0f, 1.5f, 0.0f);
	image->sphere->next->next->radius = 0.5f;
	image->sphere->next->next->color = ft_create_vec3(0.0f, 1.0f, 1.0f);
	image->sphere->next->next->index = 2;

	image->sphere->next->next->next = ft_calloc(sizeof(t_sphere), 1);
	image->sphere->next->next->next->position = ft_create_vec3(1.0f, 1.5f, 0.0f);
	image->sphere->next->next->next->radius = 1.0f;
	image->sphere->next->next->next->color = ft_create_vec3(1.0f, 0.0f, 0.0f);
	image->sphere->next->next->next->index = 3;

	image->cylinder->position = ft_create_vec3(-7.0f, 0.0f, -3.0f);
	image->cylinder->radius = 1.0f;
	image->cylinder->height = 2.0f;
	image->cylinder->normal = ft_create_vec3(1.0f, 0.0f, 0.0f);
	image->cylinder->color = ft_create_vec3(1.0f, 1.0f, 1.0f);
=======
	// image->sphere->next->next = ft_calloc(sizeof(t_sphere), 1);
	// image->sphere->next->next->position = ft_create_vec3(-1.0f, 1.5f, 0.0f);
	// image->sphere->next->next->radius = 0.5f;
	// image->sphere->next->next->color = ft_create_vec3(0.0f, 1.0f, 1.0f);

	// image->sphere->next->next->next = ft_calloc(sizeof(t_sphere), 1);
	// image->sphere->next->next->next->position = ft_create_vec3(1.0f, 1.5f, 0.0f);
	// image->sphere->next->next->next->radius = 1.0f;
	// image->sphere->next->next->next->color = ft_create_vec3(1.0f, 0.0f, 0.0f);

	image->cylinder->position = ft_create_vec3(-3.0f, 0.0f, 0.0f);
	image->cylinder->radius = 1.0f;
	image->cylinder->height = 3.0f;
	image->cylinder->normal = ft_create_vec3(0.3f, 0.5f, 0.5f);
	image->cylinder->color = ft_create_vec3(1.0f, 1.0f, 1.0f);
	
	// image->cylinder->next = ft_calloc(sizeof(t_cylinder), 1);
	// image->cylinder->next->position = ft_create_vec3(0.0f, 0.0f, 0.0f);
	// image->cylinder->next->radius = 1.0f;
	// image->cylinder->next->height = 3.0f;
	// image->cylinder->next->normal = ft_create_vec3(0.0f, 1.0f, 0.0f);
	// image->cylinder->next->color = ft_create_vec3(1.0f, 1.0f, 1.0f);
	// image->cylinder->next->type = ft_select_type(image->cylinder->next->normal);
	
	// image->cylinder->next->next = ft_calloc(sizeof(t_cylinder), 1);
	// image->cylinder->next->next->position = ft_create_vec3(3.0f, 0.0f, 0.0f);
	// image->cylinder->next->next->radius = 1.0f;
	// image->cylinder->next->next->height = 3.0f;
	// image->cylinder->next->next->normal = ft_create_vec3(0.0f, 0.0f, 1.0f);
	// image->cylinder->next->next->color = ft_create_vec3(1.0f, 1.0f, 1.0f);
	// image->cylinder->next->next->type = ft_select_type(image->cylinder->next->next->normal);
>>>>>>> c5122ce (Inicio de Norminette)

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

<<<<<<< HEAD
	image->color->light_dir.x = 2.0f;
	image->color->light_dir.y = 2.0f;
	image->color->light_dir.z = 2.0f;
=======
	image->color->light_dir.x = -4.0f;
	image->color->light_dir.y = 0.0f;
	image->color->light_dir.z = 0.0f;
>>>>>>> c5122ce (Inicio de Norminette)

	image->aspect_ratio = (float)image->width / (float)image->height;
}
