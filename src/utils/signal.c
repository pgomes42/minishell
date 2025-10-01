/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:25:28 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/24 14:28:34 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_heredoc_sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	_exit(130);
}

void	ft_setup_heredoc_signals(void)
{
	signal(SIGINT, ft_heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_signals(void)
{
	ft_disable_ctrl_echo();
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
