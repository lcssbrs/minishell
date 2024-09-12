/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:36:56 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 06:53:34 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_len(char *str)
{
	char	quote;
	int		len;

	len = 0;
	quote = '\0';
	while (str[len])
	{
		if (quote == '\0' && is_metacharacter(str[len]))
			break ;
		if (quote == '\0' && str[len] == '\'')
			quote = '\'';
		else if (quote == '\0' && str[len] == '"')
			quote = '"';
		else if (quote == '\'' && str[len] == '\'')
			quote = '\0';
		else if (quote == '"' && str[len] == '"')
			quote = '\0';
		len++;
	}
	return (len);
}

//return the longest operator found at start of str
const char	*find_operator(char *str)
{
	const char	*longest_operator;
	int			longest_operator_len;
	int			operator_len;
	int			i;

	longest_operator = NULL;
	longest_operator_len = 0;
	i = 0;
	while (operators_set()[i])
	{
		operator_len = ft_strlen(operators_set()[i]);
		if (operator_len > longest_operator_len && \
		ft_strncmp(operators_set()[i], str, operator_len) == 0)
		{
			longest_operator = operators_set()[i];
			longest_operator_len = operator_len;
		}
		i++;
	}
	return (longest_operator);
}

char	*next_token_content(char **position)
{
	const char	*operator;
	char		*token;
	char		*p;
	int			token_len;

	p = *position;
	while (is_space(*p))
		p++;
	if (*p == '\0')
		return (NULL);
	if (is_metacharacter(*p))
	{
		operator = find_operator(p);
		if (operator)
			token_len = ft_strlen(operator);
		else
			token_len = 1;
	}
	else
		token_len = word_len(p);
	token = ft_substr(p, 0, token_len);
	*position = p + token_len;
	return (token);
}

//make a token list of input
t_list	*tokenizer(char *input)
{
	t_list	*token;
	t_list	*new_token;
	char	*position_in_input;
	char	*content;

	token = NULL;
	position_in_input = input;
	content = next_token_content(&position_in_input);
	while (content != NULL)
	{
		new_token = ft_lstnew(content);
		if (new_token == NULL)
			break ;
		ft_lstadd_back(&token, new_token);
		content = next_token_content(&position_in_input);
	}
	if (errno == ENOMEM)
	{
		ft_lstclear(&token, &free);
		return (NULL);
	}
	return (token);
}
