/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:49:35 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:40:53 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_sigint_ex(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_setup_execution(void)
{
	signal(SIGINT, ft_heredoc_sigint_ex);
	signal(SIGQUIT, SIG_IGN);
}
