/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2024/10/21 15:14:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	ft_create_render(t_mlx *data, t_image *image)
// {
// 	my_mlx_pixel_put(data, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
// }


#include <math.h>

void ft_create_render(t_mlx *data, t_image *image)
{
    int cx = image->width / 2;
    int cy = image->height / 2;
    int radius = 50;
    int radius_squared = radius * radius;
    int x, y = cy - radius;

    while (++y <= cy + radius)
    {
        x = cx - radius;
        while (++x <= cx + radius)
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius_squared)
                my_mlx_pixel_put(data, x, y, 0x00FF0000);
    }

    mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
