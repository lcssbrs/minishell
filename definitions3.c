/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:14:13 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:14:52 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char *str)
{
	if (str == NULL)
		return (0);
	if (is_metacharacter(*str))
		return (0);
	return (1);
}

int	is_bracket(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '(' || *str == ')')
		return (1);
	return (0);
}

int	is_and(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("&&", str, ft_strlen(str)))
		return (1);
	return (0);
}

int	is_or(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("||", str, ft_strlen(str)))
		return (1);
	return (0);
}

int	is_left_arrow(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("<", str, -1))
		return (1);
	return (0);
}
