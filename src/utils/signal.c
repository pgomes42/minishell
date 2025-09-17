/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:25:28 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/16 12:22:06 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

void    ft_sigint_handler(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    ft_putstr_fd("\n", 1);
    rl_on_new_line();
    rl_redisplay();
    g_status = 130;
}

void ft_setup_signals(void)
{
    signal(SIGINT, ft_sigint_handler); 
    signal(SIGQUIT, SIG_IGN);          
}