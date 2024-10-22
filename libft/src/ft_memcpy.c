/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:50:32 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t		i;
	char		*dest;
	const char	*s;

	if (src == NULL && dst == NULL)
		return (NULL);
	dest = (char *)dst;
	s = (const char *)src;
	i = 0;
	while (i < num)
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}
