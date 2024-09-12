/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:47:15 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 01:24:35 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s2[i] == s1[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_getcwd(char *env, char *pwd, char *choose)
{
	if (getcwd(pwd, PATH_MAX) != NULL)
		env = ft_strjoin(choose, pwd);
	return (env);
}

char	**changeenvdir(char **env, int i, char *pwd)
{
	char	*tmp;

	i = ft_findoldpwd(env);
	tmp = env[i];
	if (env[i] && i != ft_lentab(env) && ft_findpwd(env) != ft_lentab(env))
	{
		env[i] = ft_strjoin("OLDPWD=", env[ft_findpwd(env)] + 4);
		free(tmp);
	}
	i = ft_findpwd(env);
	tmp = env[i];
	if (env[i] && i != ft_lentab(env))
	{
		env[i] = ft_getcwd(env[i], pwd, "PWD=");
		free(tmp);
	}
	return (env);
}

void	ft_else(char **arg, char ***env, int i, char *pwd)
{
	if (chdir(arg[0]) != 0)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd("cd :", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putendl_fd(": no such file or directory", 2);
		*m_exit_code() = 1;
	}
	else
		changeenvdir((*env), i, pwd);
}
