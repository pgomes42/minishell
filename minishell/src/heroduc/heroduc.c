/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heroduc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgonga4242 <sgonga4242@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:40:56 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:51:47 by sgonga4242       ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	exit(SIGINT);
}

static bool	ft_leave(t_data *data, int p[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, handle_sigquit);
	data->signint_child = false;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

static void	ft_heredoc(t_data *data, t_token *current_token, int p[2])
{
	char	*line;
	char	*quotes;
	
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, ft_heredoc_sigint_handler);

	quotes = current_token->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(current_token->value, line))
			break ;
		if (!*quotes)
			ft_heredoc_expander(data, line, p[1]);
		else
			(ft_putstr_fd(line, p[1]),ft_putstr_fd("\n", p[1]));
	}
	(ft_clean_ms(data),exit(0));
}

void	ft_init_heroduc(t_data *data)
{
	t_token	*tmp;
	int		p[2];
	int		pid;
	
	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == 3)
		{
			data->signint_child = true;
			signal(SIGINT, handle_sigint_heredoc);
			pid = (pipe(p), signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_heredoc(data, tmp->next, p);
			if (ft_leave(data, p, &pid))
			{
				data->signint_child = false;
				data->heredoc_sigint = true;
				return ;
			}
			data->here_doc = p[0];
		}
		tmp = tmp->next;
	}
}
