/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:27:24 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*arr;

	len = 0;
	while (s[len] != '\0')
		len++;
	arr = (char *)malloc(len + 1);
	if (arr == NULL)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
	{
		arr[len] = s[len];
		len++;
	}
	arr[len] = '\0';
	return (arr);
}
