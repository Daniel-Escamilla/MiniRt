/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:25:27 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 17:09:15 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_list;
	t_list	*next_node;

	if (lst != NULL && *lst != NULL && del != NULL)
	{
		current_list = *lst;
		while (current_list != NULL)
		{
			next_node = current_list->next;
			del(current_list->content);
			free(current_list);
			current_list = next_node;
		}
	}
	*lst = NULL;
}
