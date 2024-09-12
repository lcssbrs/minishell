/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:45:56 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/16 22:28:56 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(char **arg, char ***env)
{
	char	pwd[PATH_MAX];

	(void)arg;
	(void)env;
	if (getcwd(pwd, PATH_MAX) != NULL)
		printf("%s\n", pwd);
	if (errno == ENOMEM)
		return (1);
	return (0);
}
