/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:33:59 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 05:18:26 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strequal(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkexist(char *arg, char *env)
{
	int	i;

	i = 0;
	if (ft_strequal(arg) == 1)
		return (0);
	while (arg[i] == env[i] && arg[i] && env[i])
		i++;
	if (!arg[i] && !env[i])
		return (1);
	if (!arg[i] && env[i] == '=')
		return (1);
	return (0);
}

char	**ft_realloc(char **env, int change)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	temp = malloc(sizeof(char *) * i);
	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != change)
		{
			temp[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	return (temp);
}

int	ft_while(char **arg, char ***env, int j, int *i)
{
	char	**env_cpy;

	j = -1;
	while ((*env)[++j])
	{
		if (ft_checkexist(arg[*i], (*env)[j]) == 1)
		{
			env_cpy = *env;
			*env = ft_realloc(*env, j);
			freetab(env_cpy);
			if (!(*env))
				return (1);
			break ;
		}
	}
	*i += 1;
	return (0);
}

int	unset_builtin(char **arg, char ***env)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (arg[0] == NULL)
		return (0);
	if (arg[0][0] == '-')
	{
		ft_putstr_fd("minishell: unset does not take any option.\n", 2);
		*m_exit_code() = 1;
		if (errno == ENOMEM)
			return (1);
		return (0);
	}
	while (arg[i])
		if (ft_while(arg, env, j, &i) == 1)
			if (errno == ENOMEM)
				return (1);
	return (0);
}
