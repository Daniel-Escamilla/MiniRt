/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:37:24 by descamil          #+#    #+#             */
/*   Updated: 2024/10/21 14:46:04 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hooks.h"

int ft_key_hook(int key, t_image *data)
{
	printf("Tecla: %d\n", key);
	if (key == 65307 || key == 113)
		ft_end_program(data);
	return (0);
}