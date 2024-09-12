/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:54:26 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/16 17:44:33 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_i_zero(char **tmp, char **str, char ***tab, int *i)
{
	(*tmp) = ft_strdup((*tab)[*i]);
	if (!(*tmp))
		return (1);
	(*str) = ft_strjoin((*tmp), "\n");
	if (!(*str))
	{
		free((*tmp));
		return (1);
	}
	free ((*tmp));
	return (0);
}

int	ft_normsetp(char **str, char **tmp)
{
	if (!(*str))
	{
		free((*tmp));
		return (1);
	}
	return (0);
}

int	ft_firststep(char **tmp, char **str, char ***tab, int *i)
{
	(*tmp) = ft_strdup((*str));
	if (!(*tmp))
	{
		free((*str));
		return (1);
	}
	free((*str));
	(*str) = ft_strjoin((*tmp), (*tab)[*i]);
	if (ft_normsetp(str, tmp))
		return (1);
	free((*tmp));
	(*tmp) = ft_strdup((*str));
	if (!(*tmp))
	{
		free((*str));
		return (1);
	}
	free((*str));
	(*str) = ft_strjoin((*tmp), "\n");
	if (ft_normsetp(str, tmp))
		return (1);
	free((*tmp));
	return (0);
}

int	ft_secondstep(char **tmp, char **str, char ***tab, int *i)
{
	(*tmp) = ft_strdup((*str));
	if (!(*tmp))
	{
		free((*str));
		return (1);
	}
	free((*str));
	(*str) = ft_strjoin((*tmp), (*tab)[*i]);
	if (!(*str))
	{
		free((*tmp));
		return (1);
	}
	free((*tmp));
	return (0);
}

char	*ft_reverse_split(char **tab)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while (tab[i + 1])
	{
		if (i == 0)
		{
			if (ft_i_zero(&tmp, &str, &tab, &i) == 1)
				return (NULL);
		}
		else
		{
			if (ft_firststep(&tmp, &str, &tab, &i) == 1)
				return (NULL);
		}
		i++;
	}
	if (ft_secondstep(&tmp, &str, &tab, &i) == 1)
		return (NULL);
	return (str);
}
