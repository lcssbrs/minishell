/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_list_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:24:55 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:26:07 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_list_operator(t_list *token)
{
	while (token != NULL && !is_list_operator(token->content))
		token = token->next;
	return (token);
}
