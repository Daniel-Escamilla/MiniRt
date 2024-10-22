/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:45:41 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:54:46 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	end = s1 + ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (end > s1 && ft_strchr(set, *(end - 1)))
		end--;
	if (end <= s1)
		return (ft_substr("", 0, 0));
	return (ft_substr(s1, 0, end - s1));
}
