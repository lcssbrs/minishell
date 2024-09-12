/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdornic <gdornic@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:55:50 by lseiberr          #+#    #+#             */
/*   Updated: 2023/12/17 05:50:29 by gdornic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signalquit(int sig)
{
	(void)sig;
	*m_last_exit_code() = 128 + SIGQUIT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signalnewline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	*m_last_exit_code() = 128 + SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_here_doc(int sig)
{
	exit(sig);
}

void	signal_do_nothing(int sig)
{
	write(1, "\n", 1);
	*m_last_exit_code() = 128 + sig;
}
