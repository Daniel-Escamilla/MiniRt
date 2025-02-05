/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2025/02/05 11:24:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_hooks(int key, t_image *image)
{
	if (key == 65307)
		ft_end_program(image);
	return (0);
}

int main(int argc, char **argv)
{
	t_image image;

	(void) argc;
	(void) argv;
	ft_initialize(&image);
	ft_create_window(image.data, &image);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_hooks, &image);
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	mlx_loop(image.mlx); 
	return (0);
}
