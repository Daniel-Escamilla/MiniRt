/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2024/12/21 20:20:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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
