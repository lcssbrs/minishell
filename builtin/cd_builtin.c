/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:49:42 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 00:22:56 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_findoldpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'O' && env[i][1] == 'L' && env[i][2] == 'D' \
		&& env[i][3] == 'P' && env[i][4] == 'W' && env[i][5] == 'D')
			break ;
		i++;
	}
	return (i);
}

int	ft_findpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
			break ;
		i++;
	}
	return (i);
}

char	**cd_home(char **env, int i, char *pwd)
{
	char	*tmp;

	i = ft_findoldpwd(env);
	tmp = env[i];
	if (env[i] && i != ft_lentab(env))
	{
		env[i] = ft_getcwd(env[i], pwd, "OLDPWD=");
		free(tmp);
	}
	i = ft_findpwd(env);
	chdir(getenv("HOME"));
	tmp = env[i];
	if (env[i] && i != ft_lentab(env))
	{
		env[i] = ft_getcwd(env[i], pwd, "PWD=");
		free(tmp);
	}
	return (env);
}

char	*ft_strjoincpy(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

int	cd_builtin(char **arg, char ***env)
{
	int		i;
	char	pwd[PATH_MAX];

	i = 0;
	if ((*env) == NULL)
		return (0);
	if (arg[0] == NULL || ft_strcmp(arg[0], "~") == 0)
		(*env) = cd_home((*env), i, pwd);
	else if (arg[1] != NULL)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd("cd : too many arguments\n", 2);
		*m_exit_code() = 1;
	}
	else
	{
		if (ft_strcmp(arg[0], "-") == 0)
			chdir((*env)[ft_findoldpwd((*env))] + 7);
		else
			ft_else(arg, env, i, pwd);
	}
	if (errno == ENOMEM)
		return (1);
	return (0);
}
