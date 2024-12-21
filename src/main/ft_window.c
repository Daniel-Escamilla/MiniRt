/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:20:29 by descamil          #+#    #+#             */
/*   Updated: 2024/12/21 20:20:24 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_end_program(t_image *image)
{
	mlx_destroy_window(image->mlx, image->mlx_win);
	free(image->cylinder);
	free(image->sphere);
	exit (0);
	return (0);
}

void	ft_create_window(t_mlx *data, t_image *image)
{
	image->mlx = mlx_init();
	image->mlx_win = mlx_new_window(image->mlx, image->width, image->height, "MiniRT");
	if (image->mlx_win == NULL)
		ft_end_program(image);
	data->img = mlx_new_image(image->mlx, image->width, image->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}
