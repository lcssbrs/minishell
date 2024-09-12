/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:11:59 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:13:30 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_right_arrow(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp(">", str, -1))
		return (1);
	return (0);
}

int	is_double_left_arrow(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("<<", str, -1))
		return (1);
	return (0);
}

int	is_double_right_arrow(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp(">>", str, -1))
		return (1);
	return (0);
}

int	is_executable(char *path_name)
{
	if (access(path_name, F_OK))
		return (0);
	if (access(path_name, X_OK))
	{
		*m_exit_code() = 126;
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd(path_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp(cmd, "echo", -1))
		return (1);
	if (!ft_strncmp(cmd, "cd", -1))
		return (1);
	if (!ft_strncmp(cmd, "pwd", -1))
		return (1);
	if (!ft_strncmp(cmd, "export", -1))
		return (1);
	if (!ft_strncmp(cmd, "unset", -1))
		return (1);
	if (!ft_strncmp(cmd, "env", -1))
		return (1);
	if (!ft_strncmp(cmd, "exit", -1))
		return (1);
	return (0);
}
