/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_rule.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:30:22 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:30:34 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_rule(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && str[i] == '\'')
			quote = '\'';
		else if (quote == '\0' && str[i] == '"')
			quote = '"';
		else if (quote == '\'' && str[i] == '\'')
			quote = '\0';
		else if (quote == '"' && str[i] == '"')
			quote = '\0';
		i++;
	}
	if (quote != '\0')
		return (1);
	return (0);
}
