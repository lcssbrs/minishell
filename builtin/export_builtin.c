/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:41:27 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:04:26 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../minishell.h>

char	**ft_add_env(char **env, char *arg)
{
	int		len;
	char	**tmp;
	int		i;

	len = ft_lentab(env);
	i = -1;
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	while (env[++i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
			return (NULL);
	}
	tmp[i] = ft_strdup(arg);
	if (!tmp[i])
		return (NULL);
	tmp[i + 1] = NULL;
	freetab(env);
	return (tmp);
}

char	**modify_env(char **env, char *arg)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (lentillequall(arg) == lentillequall(env[i]) && \
		ft_strncmp(env[i], arg, lentillequall(arg)) == 0 && \
		ft_chr(arg, '=') == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(arg);
		}
	}
	return (env);
}

char	**cpytab(char **sort)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (ft_lentab(sort) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (sort[i])
	{
		new[i] = ft_strdup(sort[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	printexport(char ***env)
{
	int		i;
	char	**sort;
	char	**split_tmp;

	i = 0;
	sort = sort_env(*env);
	while (sort[i])
	{
		split_tmp = ft_split(sort[i], '=');
		if (split_tmp == NULL)
			break ;
		printf("declare x ");
		printf("%s", split_tmp[0]);
		if (split_tmp[1] != NULL)
			printf("=\"%s\"", split_tmp[1]);
		printf("\n");
		array_free(split_tmp, 2);
		i++;
	}
	freetab(sort);
}

int	export_builtin(char **arg, char ***env)
{
	int	i;

	i = -1;
	if (!arg[0])
		printexport(env);
	else if (arg[0] && arg[0][0] == '-')
	{
		ft_putstr_fd("export don't take option\n", 2);
		return (0);
	}
	while (arg[++i])
	{
		if (check_syntax(arg[i]) == 0 && checkarg((*env), arg[i]) == 0)
			(*env) = ft_add_env((*env), arg[i]);
		else if (check_syntax(arg[i]) == 0 && checkarg(*env, arg[i]) == 1)
			(*env) = modify_env((*env), arg[i]);
	}
	return (0);
}
