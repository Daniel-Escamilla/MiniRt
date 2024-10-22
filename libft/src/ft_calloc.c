/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:01:10 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:58:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	total_size;
	char	*ptr_chr;

	if ((nmemb == SIZE_MAX) || (size == SIZE_MAX))
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ptr_chr = (char *)ptr;
	while (i < total_size)
	{
		ptr_chr[i] = 0;
		i++;
	}
	return (ptr);
}
