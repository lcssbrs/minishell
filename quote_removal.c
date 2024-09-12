/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 03:40:13 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 07:42:59 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_quote(char *word, char previous_quote)
{
	if (previous_quote == '\0')
	{
		while (*word != '\0' && *word != '"' && *word != '\'')
			word++;
		return (word);
	}
	while (*word != '\0' && *word != previous_quote)
		word++;
	return (word);
}

char	*quote_purge(char *word)
{
	char	*word_cpy;
	char	*purge;
	char	*quote;

	if (word == NULL)
		return (NULL);
	word_cpy = word;
	quote = next_quote(word, '\0');
	purge = ft_strdup("");
	while (*word != '\0')
	{
		purge = str_merge(purge, ft_substr(word, 0, quote - word));
		if (purge == NULL)
			break ;
		word = quote + (*quote == '\'' || *quote == '"');
		quote = next_quote(word, *quote);
		purge = str_merge(purge, ft_substr(word, 0, quote - word));
		if (purge == NULL)
			break ;
		word = quote + (*quote == '\'' || *quote == '"');
		quote = next_quote(word, '\0');
		purge = str_merge(purge, ft_substr(word, 0, quote - word));
	}
	free(word_cpy);
	return (purge);
}

//use with dynamic allocation
char	*quote_remove_core(char *word)
{
	char	*unquoted_word;
	char	*separator;

	unquoted_word = ft_strdup("");
	separator = next_mark(word);
	while (*word != '\0')
	{
		unquoted_word = str_merge(unquoted_word, \
		quote_purge(ft_substr(word, 0, separator - word)));
		if (unquoted_word == NULL)
			break ;
		word = separator + (*separator == '\x1D');
		separator = next_mark(word);
		unquoted_word = str_merge(unquoted_word, \
		ft_substr(word, 0, separator - word));
		if (unquoted_word == NULL)
			break ;
		word = separator + (*separator == '\x1D');
		separator = next_mark(word);
	}
	return (unquoted_word);
}

char	*quote_remove(char *word)
{
	char	*word_cpy;
	char	*unquoted_word;

	if (word == NULL)
		return (NULL);
	word_cpy = word;
	unquoted_word = quote_remove_core(word);
	free(word_cpy);
	return (unquoted_word);
}

t_list	*quote_removal(t_list *token)
{
	t_list	*unquoted_token;
	t_list	*new;

	unquoted_token = NULL;
	while (token != NULL)
	{
		new = lstnew_secure(quote_remove(ft_strdup(token->content)));
		if (new == NULL)
			break ;
		ft_lstadd_back(&unquoted_token, new);
		token = token->next;
	}
	if (errno == ENOMEM)
		ft_lstclear(&unquoted_token, &free);
	return (unquoted_token);
}
