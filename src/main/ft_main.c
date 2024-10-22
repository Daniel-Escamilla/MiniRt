/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2024/10/21 14:49:41 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	main(int argc, char **argv)
{
	t_image	image;
	t_mlx	data;

	(void) argc;
	(void) argv;
	ft_initialize(&image);
	ft_create_window(&data, &image);
	ft_create_render(&data, &image);
	mlx_key_hook(image.mlx_win, ft_key_hook, &image);
	mlx_loop(image.mlx);
	return (0);
}
