/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:56:24 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:44 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destino;
	const char	*origen;

	origen = (const char *)src;
	destino = (char *)dest;
	if (destino == NULL && origen == NULL)
		return (NULL);
	if (destino <= origen || destino >= (origen + n))
		while (n--)
			*(destino++) = *(origen++);
	else
	{
		destino += n - 1;
		origen += n - 1;
		while (n--)
			*(destino--) = *(origen--);
	}
	return (dest);
}
