/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:55:13 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	unsigned char		caracter;

	i = 0;
	s1 = (const unsigned char *)s;
	caracter = (unsigned char)c;
	while (i < n)
	{
		if (s1[i] == caracter)
			return ((void *)s1 + i);
		i++;
	}
	return (NULL);
}
