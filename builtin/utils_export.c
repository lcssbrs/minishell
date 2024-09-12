/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:04:43 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:04:58 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lentillequall(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	ft_lentab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if ((arg[0] < 'a' || arg[0] > 'z') && (arg[0] < 'A' || arg[0] > 'Z'))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (arg[i])
	{
		if ((arg[i] < 'a' || arg[i] > 'z') && (arg[i] < 'A' || \
		arg[i] > 'Z') && arg[i] < '0' && arg[i] > '9')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	checkarg(char **env, char *arg)
{
	int		i;
	char	**split_env;
	char	**split_arg;

	i = 0;
	split_arg = ft_split(arg, '=');
	if (split_arg == NULL)
		return (0);
	while (env[i])
	{
		split_env = ft_split(env[i], '=');
		if (split_env == NULL)
			break ;
		if (ft_strcmp(split_arg[0], split_env[0]) == 0 && ft_chr(arg, '=') == 0)
		{
			freetab(split_arg);
			freetab(split_env);
			return (1);
		}
		freetab(split_env);
		i++;
	}
	freetab(split_arg);
	return (0);
}
