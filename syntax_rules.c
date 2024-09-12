/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:27:35 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 07:30:14 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *content)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (content != NULL)
		ft_putstr_fd(content, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	bracket_count_rule(char *content, char *next_content)
{
	static int	left_bracket_count = 0;
	static int	right_bracket_count = 0;

	if (content == NULL)
	{
		left_bracket_count = 0;
		right_bracket_count = 0;
	}
	if (is_left_bracket(content))
		left_bracket_count++;
	if (is_right_bracket(content))
		right_bracket_count++;
	if (right_bracket_count > left_bracket_count)
		return (syntax_error(content));
	if (next_content == NULL && left_bracket_count != right_bracket_count)
		return (syntax_error(next_content));
	return (0);
}

int	operator_rules(char *content, char *next_content)
{
	if (is_redirection_operator(content) && !(is_word(next_content)))
		return (syntax_error(next_content));
	else if (is_pipe(content) && (!(is_word(next_content) \
	|| is_redirection_operator(next_content))))
		return (syntax_error(next_content));
	else if (is_list_operator(content) && (!(is_word(next_content) || \
	is_redirection_operator(next_content) || is_left_bracket(next_content))))
		return (syntax_error(next_content));
	else if (is_left_bracket(content) && (!(is_word(next_content) || \
	is_redirection_operator(next_content) || is_left_bracket(next_content))))
		return (syntax_error(next_content));
	else if (is_right_bracket(content) && (!(is_right_bracket(next_content) || \
	is_list_operator(next_content) || next_content == NULL)))
		return (syntax_error(next_content));
	if (bracket_count_rule(content, next_content))
		return (1);
	return (0);
}

int	word_rules(char *content, char *next_content)
{
	if (quotes_rule(content))
		return (syntax_error(next_content));
	if (bracket_count_rule(content, next_content))
		return (1);
	return (0);
}

//describe every rules for tokens as "what can be next to the token"
int	syntax_rules(t_list *token)
{
	char	*content;
	char	*next_content;

	content = token->content;
	if (token->next != NULL)
		next_content = token->next->content;
	else
		next_content = NULL;
	if (is_word(content))
		return (word_rules(content, next_content));
	else if (is_operator(content))
		return (operator_rules(content, next_content));
	else
		return (syntax_error(content));
	return (0);
}
