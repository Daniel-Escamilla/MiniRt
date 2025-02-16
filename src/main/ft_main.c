/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2025/02/16 16:39:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// void	ft_circle(int key, t_image *image)
// {
// 	if (key == 65362 && image->sphere->radius > 0.0f)
// 		image->sphere->radius -= 0.01f;
// 	if (key == 65364)
// 		image->sphere->radius += 0.01f;
// }

void	ft_lights(int key, t_image *image)
{
	if (key == RIGHT)
		image->color->light_dir.x -= 0.2f;
	if (key == LEFT)
		image->color->light_dir.x += 0.2f;
	if (key == UP)
		image->color->light_dir.y -= 0.2f;
	if (key == DOWN)
		image->color->light_dir.y += 0.2f;
	if (key == FORWARD)
		image->color->light_dir.z -= 0.2f;
	if (key == BACKWARD)
		image->color->light_dir.z += 0.2f;
}

// int render_next_frame(t_image *image)
// {
//     update_light_position(image);
//     ft_create_render(image->data, image);
//     return (0);
// }

// void	ft_moon(int key, t_image *image)
// {
// 	if (key == M)
//     {
//         mlx_loop_hook(image->mlx, render_next_frame, image);
// 	}
// }

int ft_key_hook(int key, t_image *image)
{
	printf("Tecla: %d\n", key);
	if (key == 65307 || key == 113)
		ft_end_program(image);
	// ft_circle(key, image);
	ft_lights(key, image);
	// ft_moon(key, image);
    if (key != M)
	    ft_create_render(image->data, image);
	return (0);
}

// int	ft_hooks(int key, t_image *image)
// {
// 	if (key == 65307)
// 		ft_end_program(image);
// 	return (0);
// }

int main(int argc, char **argv)
{
	t_image image;

	(void) argc;
	(void) argv;
	ft_initialize(&image);
	ft_create_window(image.data, &image);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_key_hook, &image);
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	mlx_loop(image.mlx); 
	return (0);
}
