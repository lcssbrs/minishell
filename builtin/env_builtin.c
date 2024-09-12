/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:36:54 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 00:50:36 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkafterequal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	env_builtin(char **arg, char ***env)
{
	int	i;

	i = 0;
	if (arg[0] != NULL)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd("invalid argument quantity\n", 2);
		*m_exit_code() = 1;
		return (0);
	}
	while ((*env)[i])
	{
		if (ft_chr((*env)[i], '=') == 0 && checkafterequal((*env)[i]) == 0)
			printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}
