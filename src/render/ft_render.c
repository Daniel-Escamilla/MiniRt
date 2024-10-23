/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:28:29 by descamil          #+#    #+#             */
/*   Updated: 2024/10/23 23:46:18 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// uint8_t		r;
// uint8_t		g;
// r = (uint8_t)(coord.x * 255.0f);
// g = (uint8_t)(coord.y * 255.0f);
// color = 0x000000 | (r << 16) | (g << 8);

uint32_t	ft_per_pixel(t_image *image, t_vec2 coord)
{
	uint32_t	color;
	t_vec3		ray_dir;		// a
	t_vec3		ray_origin;		// b
	float		discriminate;
	t_vec2		result;
	float		a;
	float		b;
	float		c;
	float		r;

	coord.x *= image->aspect_ratio;
	
	ray_dir.x = coord.x;
	ray_dir.y = coord.y;
	ray_dir.z = 1;

	ray_origin.x = 0.0f;
	ray_origin.y = 0.0f;
	ray_origin.z = 2.0f;

	
// ( bx² ​+ by² ​+ bz² ​)t² + 2(ax​bx ​+ ay​by ​+ az​bz​)t + (ax²​ + ay² + az² − r²) = 0
// a = ray_direction
// b = ray_origin
// r = radius
// t = hit distant



	r = 0.5f;
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = 2.0f * (ray_dir.x * ray_origin.x + ray_dir.y * ray_origin.y + ray_dir.z * ray_origin.z);
	c = (ray_origin.x * ray_origin.x + ray_origin.y * ray_origin.y + ray_origin.z * ray_origin.z) - r * r;

	discriminate = b * b - 4.0f * a * c;
	if (discriminate >= 0)
	{
		color = 0xff0ff000;
		result.x = (-b + sqrt(discriminate)) / 2 * a; // Resultado cordenada negativa;
		result.y = (-b -  sqrt(discriminate)) / 2 * a; // Resultado cordenada positiva;
		// printf("%f\n", result);
		// printf("Coord.x --> %f\n", coord.x);
		// printf("Coord.y --> %f\n", coord.y);
	}
	else
		color = 0x00000000;

	return (color);
}

void	ft_create_render(t_mlx *data, t_image *image)
{
	uint32_t	color;
	t_vec2		coord;
	int			y;
	int			x;

	y = 0;
	
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			coord.x = ((float)x / (float)image->width);
			coord.y = ((float)y / (float)image->height);
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;
			color = ft_per_pixel(image, coord);
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
