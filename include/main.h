/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:10 by descamil          #+#    #+#             */
/*   Updated: 2025/02/18 17:35:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minirt.h"

// ft_initialize.c
void	ft_initialize(t_image *image);
void	print_objects(t_objects *objects);

// ft_window.c
int		ft_end_program(t_image *image);
void	ft_create_window(t_mlx *data, t_image *image);

#endif
