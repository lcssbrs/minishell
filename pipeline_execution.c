/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:44:33 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 08:46:19 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_null_content(t_list **lst)
{
	t_list	*i;
	t_list	*j;

	if (lst == NULL)
		return ;
	i = *lst;
	while (i != NULL)
	{
		if (i->content == NULL || ft_strlen(i->content) == 0)
		{
			j = i->next;
			delete_node(lst, i);
			i = j;
		}
		else
			i = i->next;
	}
}

t_list	*next_expanded_command(t_list *pipeline, char **envp)
{
	t_list	*command;
	t_list	*new;

	command = NULL;
	while (pipeline != NULL && !is_pipe(pipeline->content))
	{
		if (is_redirection_operator(pipeline->content))
		{
			new = redirection_expansion(pipeline, envp);
			pipeline = pipeline->next;
		}
		else
			new = classic_expansion(pipeline->content, envp);
		if (new == NULL)
		{
			ft_lstclear(&command, &free);
			return (NULL);
		}
		ft_lstadd_back(&command, new);
		pipeline = pipeline->next;
	}
	remove_null_content(&command);
	return (command);
}

int	pipe_initialize(int builtin_create_subshell, t_list *pipeline)
{
	if (builtin_create_subshell)
	{
		if (next_pipe(pipeline) == NULL)
		{
			if (pipe_set(1))
				return (0);
		}
		else if (pipe_set(0))
			return (0);
	}
	return (1);
}

int	pipeline_routine(t_list *pipeline, char ***envp_ptr, \
int exit_status, int builtin_create_subshell)
{
	t_list	*command;

	command = next_expanded_command(pipeline, *envp_ptr);
	if (command == NULL)
		return (errno);
	if (pipe_initialize(builtin_create_subshell, pipeline) == 0)
		return (0);
	*m_exit_code() = 0;
	exit_status = command_execution(command, \
	envp_ptr, exit_status, builtin_create_subshell);
	ft_lstclear(&command, &free);
	if (*m_exit_code() == 130)
		return (0);
	if (exit_status == ENOMEM)
		return (errno);
	pipeline = next_pipe(pipeline);
	if (pipeline == NULL)
		return (exit_status);
	return (pipeline_routine(pipeline->next, envp_ptr, \
	exit_status, builtin_create_subshell));
}

//dup2 stdin et stdout ici avant pipeline
int	pipeline_execution(t_list *pipeline, char ***envp_ptr, int exit_status)
{
	m_stream_set();
	if (dup2(m_stream()->saved_stdin_fd, 0) == -1)
		return (errno);
	if (dup2(m_stream()->saved_stdout_fd, 1) == -1)
		return (errno);
	return (pipeline_routine(pipeline, envp_ptr, \
	exit_status, next_pipe(pipeline) != NULL));
}
