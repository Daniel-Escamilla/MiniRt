/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:06:31 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:40 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	char	caracter;
	int		i;

	ptr = (char *)s;
	caracter = (char)c;
	i = 0;
	while (n != 0)
	{
		ptr[i] = caracter;
		n--;
		i++;
	}
	return (ptr);
}
