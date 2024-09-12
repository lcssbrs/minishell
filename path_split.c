/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:21:30 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 07:21:54 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_split(char **envp)
{
	char	*path_value;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path_value = envp[i] + ft_strlen("PATH=");
	return (ft_split(path_value, ':'));
}
