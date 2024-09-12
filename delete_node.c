/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 06:56:33 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 06:56:37 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//delete the node and his content, and reconnect the list
void	delete_node(t_list **list, t_list *node)
{
	t_list	*i;

	if (list == NULL || *list == NULL || node == NULL)
		return ;
	if (*list == node)
		*list = (*list)->next;
	else
	{
		i = *list;
		while (i->next != NULL && i->next != node)
			i = i->next;
		i->next = node->next;
	}
	if (node->content != NULL)
		ft_lstdelone(node, free);
	else
		free(node);
}
