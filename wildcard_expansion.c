/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:36:23 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 06:56:57 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pattern_match(t_list *pattern, char *file_name)
{
	char	*s;

	s = ft_strnstr(file_name, pattern->content, ft_strlen(file_name));
	if (s != file_name)
		return (0);
	pattern = pattern->next;
	while (pattern != NULL)
	{
		s = ft_strnstr(s, pattern->content, ft_strlen(s));
		if (s == NULL)
			return (0);
		pattern = pattern->next;
	}
	return (1);
}

char	*next_wildcard(char *word)
{
	char	quote;

	quote = '\0';
	while (*word != '\0')
	{
		if (quote != '\'' && quote != '"' && *word == '*')
			break ;
		if (quote == '\0' && *word == '\'')
			quote = '\'';
		else if (quote == '\0' && *word == '"')
			quote = '"';
		else if (quote == '\'' && *word == '\'')
			quote = '\0';
		else if (quote == '"' && *word == '"')
			quote = '\0';
		word++;
	}
	return (word);
}

t_list	*pattern_extraction(char *word)
{
	t_list	*pattern;
	t_list	*new;
	char	*separator;

	pattern = NULL;
	separator = next_wildcard(word);
	while (*word != '\0')
	{
		new = lstnew_secure(quote_remove(ft_substr(word, 0, separator - word)));
		if (new == NULL)
			break ;
		ft_lstadd_back(&pattern, new);
		word = separator + (*separator == '*');
		separator = next_wildcard(word);
	}
	if (errno == ENOMEM)
		ft_lstclear(&pattern, &free);
	return (pattern);
}

t_list	*wildcard_expansion(char *word, t_list *cwd_file)
{
	t_list	*pattern;
	t_list	*expansion;
	t_list	*new;

	pattern = pattern_extraction(word);
	if (pattern == NULL)
		return (NULL);
	expansion = NULL;
	while (cwd_file != NULL)
	{
		if (pattern_match(pattern, cwd_file->content))
		{
			new = lstnew_secure(expansion_mark(ft_strdup(cwd_file->content)));
			if (new == NULL)
				break ;
			ft_lstadd_back(&expansion, new);
		}
		cwd_file = cwd_file->next;
	}
	ft_lstclear(&pattern, &free);
	if (expansion == NULL)
		return (lstnew_secure(ft_strdup(word)));
	if (errno == ENOMEM)
		ft_lstclear(&expansion, &free);
	return (expansion);
}
