/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:21:49 by descamil          #+#    #+#             */
/*   Updated: 2024/10/30 12:20:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../minirt.h"

// ft_render.c
void	ft_create_render(t_mlx *data, t_image *image);
t_vec3	ft_create_vec3(float a, float b, float c);
t_vec3	ft_float_to_vec3(float a);

#endif
