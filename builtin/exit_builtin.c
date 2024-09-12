/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:22:00 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 02:13:34 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **arg, char ***env)
{
	if (arg != NULL && ft_lentab(arg) > 1)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putendl_fd("exit: too many arguments", 2);
		return (0);
	}
	array_free(*env, 2);
	*env = NULL;
	if (arg != NULL && arg[0] != NULL && contain_only_digit(arg[0]))
		*m_last_exit_code() = ft_atoi(arg[0]);
	else if (arg != NULL && arg[0] != NULL)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		*m_last_exit_code() = 2;
	}
	return (1);
}
