/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:54:24 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 06:56:00 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_stream_use(void)
{
	if (m_stream()->next_input != -1 && close(m_stream()->next_input))
		return (errno);
	if (m_stream()->previous_output != -1 && close(m_stream()->previous_output))
		return (errno);
	if (m_stream()->input != -1 && dup2(m_stream()->input, 0) == -1)
		return (errno);
	if (m_stream()->output != -1 && dup2(m_stream()->output, 1) == -1)
		return (errno);
	return (0);
}

int	m_stream_redirect(t_list *command)
{
	command = next_redirection_operator(command);
	while (command != NULL)
	{
		if (!ft_strncmp("<", command->content, -1) && \
		input_redirect(command->next->content))
			return (errno);
		if (!ft_strncmp("<<", command->content, -1) && \
		here_doc(command->next->content))
			return (errno);
		if (!ft_strncmp(">", command->content, -1) && \
		output_redirect(command->next->content))
			return (errno);
		if (!ft_strncmp(">>", command->content, -1) && \
		output_redirect_append(command->next->content))
			return (errno);
		command = command->next;
		command = next_redirection_operator(command);
	}
	return (0);
}

void	m_stream_set(void)
{
	m_stream()->input = -1;
	m_stream()->output = -1;
	m_stream()->next_input = -1;
	m_stream()->previous_output = -1;
}

int	pipe_set(int last)
{
	static int	pipe_fd[2] = {-1, -1};

	m_stream()->input = pipe_fd[0];
	m_stream()->previous_output = pipe_fd[1];
	if (last)
	{
		m_stream()->output = m_stream()->saved_stdout_fd;
		m_stream()->next_input = -1;
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		return (0);
	}
	if (pipe(pipe_fd))
		return (errno);
	m_stream()->output = pipe_fd[1];
	m_stream()->next_input = pipe_fd[0];
	return (0);
}
