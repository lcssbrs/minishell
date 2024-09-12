/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:15:21 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:15:54 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_list_operator(char *str)
{
	int			i;

	if (str == NULL)
		return (0);
	i = 5;
	while (i < 7)
	{
		if (ft_strncmp(operators_set()[i], str, \
		ft_strlen(operators_set()[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_pipe(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_right_bracket(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == ')')
		return (1);
	return (0);
}

int	is_left_bracket(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '(')
		return (1);
	return (0);
}
