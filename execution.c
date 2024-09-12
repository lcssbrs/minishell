/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:41:06 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 07:24:02 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_group(t_list *token)
{
	int	left_bracket_count;

	token = token->next;
	left_bracket_count = 0;
	while (token != NULL && is_left_bracket(token->content))
	{
		left_bracket_count++;
		token = token->next;
	}
	while (left_bracket_count > 0)
	{
		if (is_right_bracket(token->content))
			left_bracket_count--;
		token = token->next;
	}
	return (next_list_operator(token));
}

t_list	*and_skip(t_list *token)
{
	while (token != NULL && is_and(token->content))
		token = skip_group(token);
	return (token);
}

t_list	*or_skip(t_list *token)
{
	while (token != NULL && is_or(token->content))
		token = skip_group(token);
	return (token);
}

t_list	*next_pipeline(t_list *token)
{
	t_list	*pipeline;
	t_list	*new;
	char	*content;

	pipeline = NULL;
	while (is_bracket(token->content) || is_list_operator(token->content))
		token = token->next;
	while (token != NULL && !is_list_operator(token->content) && \
	!is_bracket(token->content))
	{
		content = ft_strdup(token->content);
		if (content == NULL)
			break ;
		new = ft_lstnew(content);
		if (new == NULL)
		{
			free(content);
			break ;
		}
		ft_lstadd_back(&pipeline, new);
		token = token->next;
	}
	if (errno == ENOMEM)
		ft_lstclear(&pipeline, &free);
	return (pipeline);
}

//step 1: make the next pipeline from the token list
//step 2: execute the pipeline
//step 3: search the next list operator, if NULL is found stop the recursion
//step 4: evaluate exit status, potentially skip the next group of pipelines
//step 5: go back to step 1 with a new position in the token list
int	execution(t_list *token, char ***envp_ptr, int exit_status)
{
	t_list	*pipeline;

	pipeline = next_pipeline(token);
	if (pipeline == NULL)
		return (errno);
	exit_status = pipeline_execution(pipeline, envp_ptr, 0);
	ft_lstclear(&pipeline, &free);
	if (*m_exit_code() == 130)
		return (0);
	if (errno == ENOMEM)
		return (errno);
	token = next_list_operator(token);
	if (token == NULL)
		return (exit_status);
	if (is_and(token->content) && *m_exit_code())
		token = and_skip(token);
	else if (is_or(token->content) && !*m_exit_code())
		token = or_skip(token);
	if (token == NULL)
		return (exit_status);
	return (execution(token->next, envp_ptr, exit_status));
}
