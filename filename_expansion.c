/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:19:41 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 06:58:12 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_file_name(DIR *dir_stream)
{
	struct dirent	*dir_entry;
	t_list			*file_name;
	t_list			*new;
	char			*content;

	file_name = NULL;
	dir_entry = readdir(dir_stream);
	while (dir_entry != NULL)
	{
		content = ft_strdup(dir_entry->d_name);
		if (content == NULL)
			break ;
		new = ft_lstnew(content);
		if (new == NULL)
		{
			free(content);
			break ;
		}
		ft_lstadd_back(&file_name, new);
		dir_entry = readdir(dir_stream);
	}
	if (errno == ENOMEM)
		ft_lstclear(&file_name, &free);
	return (file_name);
}

t_list	*get_cwd_file(void)
{
	DIR				*dir_stream;
	char			*cwd;
	t_list			*cwd_file;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	dir_stream = opendir(cwd);
	free(cwd);
	if (dir_stream == NULL)
		return (NULL);
	cwd_file = get_file_name(dir_stream);
	closedir(dir_stream);
	return (cwd_file);
}

t_list	*filename_expansion(t_list *token)
{
	t_list	*expansion;
	t_list	*cwd_file;
	t_list	*new;

	cwd_file = get_cwd_file();
	if (cwd_file == NULL)
		return (NULL);
	expansion = NULL;
	while (token != NULL)
	{
		if (*next_wildcard(token->content) == '\0')
			new = lstnew_secure(ft_strdup(token->content));
		else
			new = wildcard_expansion(token->content, cwd_file);
		if (new == NULL)
			break ;
		ft_lstadd_back(&expansion, new);
		token = token->next;
	}
	ft_lstclear(&cwd_file, &free);
	if (errno == ENOMEM)
		ft_lstclear(&expansion, &free);
	return (expansion);
}
