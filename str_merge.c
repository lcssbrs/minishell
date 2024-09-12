/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 06:13:54 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 06:49:34 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//use only on dynamically allocated strings
char	*str_merge(char *s1, char *s2)
{
	char	*merge;

	merge = ft_strjoin(s1, s2);
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (merge);
}
