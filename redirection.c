/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:10:52 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 07:40:54 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_routine(char *delimiter, int pipe_fd[2])
{
	char	*input;

	signal(SIGINT, &signal_here_doc);
	rl_clear_history();
	if (close(pipe_fd[0]))
		return (0);
	input = readline(HERE_DOC_PROMPT);
	while (input != NULL && ft_strncmp(delimiter, input, ft_strlen(input)))
	{
		if (write(pipe_fd[1], input, ft_strlen(input)) == -1 || \
		write(pipe_fd[1], "\n", 1) == -1)
			return (0);
		free(input);
		input = readline(HERE_DOC_PROMPT);
	}
	if (input != NULL)
		free(input);
	return (0);
}

int	here_doc(char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		wait_status;

	if (pipe(pipe_fd))
		return (errno);
	pid = fork();
	if (pid < 0)
		return (errno);
	if (pid == 0)
		exit(here_doc_routine(delimiter, pipe_fd));
	if (close(pipe_fd[1]))
		return (errno);
	waitpid(pid, &wait_status, 0);
	signal(SIGINT, &ft_signalnewline);
	if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status))
		*m_exit_code() = 128 + WEXITSTATUS(wait_status);
	m_stream()->input = pipe_fd[0];
	return (0);
}

int	input_redirect(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		*m_exit_code() = 1;
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	m_stream()->input = fd;
	return (0);
}

int	output_redirect(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
	{
		*m_exit_code() = 1;
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	m_stream()->output = fd;
	return (0);
}

int	output_redirect_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
	{
		*m_exit_code() = 1;
		ft_putstr_fd(ERROR_PREFIX, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	m_stream()->output = fd;
	return (0);
}
