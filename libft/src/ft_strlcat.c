/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:44:55 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:55:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;
	size_t	total;

	i = 0;
	lendst = ft_strlen(dst);
	lensrc = ft_strlen((char *) src);
	total = lendst + lensrc;
	if (size == 0)
		return (lensrc);
	if (lendst >= size)
		return (size + lensrc);
	while (lendst < size - 1 && lensrc > 0)
	{
		dst[lendst] = src[i];
		lendst++;
		lensrc--;
		i++;
	}
	dst[lendst] = '\0';
	return (total);
}
