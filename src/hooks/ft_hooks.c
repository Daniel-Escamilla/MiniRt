/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:37:24 by descamil          #+#    #+#             */
/*   Updated: 2024/10/26 23:31:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hooks.h"

void	ft_rgb(int key, t_image *image)
{
	if (key == NEG || key == SUBS)
		image->color->plus = 0;
	if (key == POS || key == PLUS)
		image->color->plus = 1;

	if (key == R && image->color->plus == 1)
		image->color->rgb.x += 0.1f;
	if (key == G && image->color->plus == 1)
		image->color->rgb.y += 0.1f;
	if (key == B && image->color->plus == 1)
		image->color->rgb.z += 0.1f;

	if (key == T)
	{
		if (image->color->rgb.x > 0.0f)
			image->color->rgb.x -= 0.1f;
		if (image->color->rgb.y > 0.0f)
			image->color->rgb.y -= 0.1f;
		if (image->color->rgb.z > 0.0f)
			image->color->rgb.z -= 0.1f;
	}
	
	if (key == R && image->color->plus == 0 && image->color->rgb.x > 0.0f)
		image->color->rgb.x -= 0.1f;
	if (key == G && image->color->plus == 0 && image->color->rgb.y > 0.0f)
		image->color->rgb.y -= 0.1f;
	if (key == B && image->color->plus == 0 && image->color->rgb.z > 0.0f)
		image->color->rgb.z -= 0.1f;
}

void	ft_circle(int key, t_image *image)
{
	if (key == 65362 && image->circle->radius > 0.0f)
		image->circle->radius -= 0.01f;
	if (key == 65364)
		image->circle->radius += 0.01f;
}

void	ft_lights(int key, t_image *image)
{
	if (key == RIGHT)
		image->color->light_dir.x -= 0.1f;
	if (key == LEFT)
		image->color->light_dir.x += 0.1f;
	if (key == UP)
		image->color->light_dir.y -= 0.1f;
	if (key == DOWN)
		image->color->light_dir.y += 0.1f;
	if (key == FORWARD)
		image->color->light_dir.z -= 0.1f;
	if (key == BACKWARD)
		image->color->light_dir.z += 0.1f;
}

void update_light_position(t_image *image)
{
    if (image->light->direction == 0)
    {
        image->color->light_dir.x += image->light->increment;
        image->color->light_dir.z += image->light->increment;
        if (image->color->light_dir.x >= 0 && image->color->light_dir.z >= 1)
        {
            image->light->direction = 1;
            image->light->count++;
        }
    }
    else if (image->light->direction == 1)
    {
        image->color->light_dir.x += image->light->increment;
        image->color->light_dir.z -= image->light->increment;
        if (image->color->light_dir.x >= 1 && image->color->light_dir.z <= 0)
        {
            image->light->direction = 2;
            image->light->count++;
        }
    }
    else if (image->light->direction == 2)
    {
        image->color->light_dir.x -= image->light->increment;
        image->color->light_dir.z -= image->light->increment;
        if (image->color->light_dir.x <= 0 && image->color->light_dir.z <= -1)
        {
            image->light->direction = 3;
            image->light->count++;
        }
    }
    else if (image->light->direction == 3)
    {
        image->color->light_dir.x -= image->light->increment;
        image->color->light_dir.z += image->light->increment;
        if (image->color->light_dir.x <= -1 && image->color->light_dir.z >= 0)
        {
            image->light->direction = 0;
            image->light->count++;
        }
    }
    if (image->light->count >= 4)
    {
        printf("La luz ha pasado por los 4 puntos.\n");
        mlx_loop_end(image->mlx);
    }
}

int render_next_frame(t_image *image)
{
    update_light_position(image);
    ft_create_render(image->data, image);
    return (0);
}

void	ft_moon(int key, t_image *image)
{
	if (key == M)
    {
        image->light->count = 0;
        image->light->direction = 0;
        image->light->increment = 0.05f;
        mlx_loop_hook(image->mlx, render_next_frame, image);
	}
}

int ft_key_hook(int key, t_image *image)
{
	printf("Tecla: %d\n", key);
	if (key == 65307 || key == 113)
		ft_end_program(image);
	ft_circle(key, image);
	// ft_lights(key, image);
	// ft_rgb(key, image);
    if (key != M && key != W && key != A && key != S && key != D)
	    ft_create_render(image->data, image);
    
	// ft_moon(key, image);
	return (0);
}