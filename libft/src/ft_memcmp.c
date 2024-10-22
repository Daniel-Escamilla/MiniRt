/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:23:42 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*v1;
	const unsigned char	*v2;

	i = 0;
	v1 = (const unsigned char *)s1;
	v2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (v1[i] == v2[i])
			i++;
		else
			return (v1[i] - v2[i]);
	}
	return (0);
}
