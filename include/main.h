/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:10 by descamil          #+#    #+#             */
/*   Updated: 2024/10/19 00:28:24 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minirt.h"

// ft_initialize.c
void	ft_initialize(t_image *image);

// ft_window.c
void	ft_end_program(t_image *image);
void	ft_create_window(t_mlx *data, t_image *image);

#endif
