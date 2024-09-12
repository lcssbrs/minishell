/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 08:45:54 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 08:46:15 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_pipe(t_list *pipeline)
{
	while (pipeline != NULL && !is_pipe(pipeline->content))
		pipeline = pipeline->next;
	return (pipeline);
}
