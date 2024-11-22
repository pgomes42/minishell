/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:38:42 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 13:29:43 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_status = 0;

void	ft_set_parse_err(t_data *data, t_parse_err_type type)
{
	data->parse_err.type = type;
}

void	ft_handle_parse_err(t_data *data)
{
	t_parse_err_type	type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_IDENTIFIER", "<", ">", "<<", ">>", "|", "(", ")",
		"&&", "||", "newline"};
	type = data->parse_err.type;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type == E_SYNTAX)
		{
			if (!data->curr_token)
				token_type = T_NL;
			else
				token_type = data->curr_token->type;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			data->exit_s = 2;
		}
		ft_clear_token_list(&data->tokens);
		ft_bzero(&data->parse_err, sizeof(t_parse_err));
	}
}

static void	ft_init_minishell(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->environ = env;
	ft_init_envlst(data);
	data->stdin = dup(0);
	data->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &data->original_term);
}

static void	ft_start_execution(t_data *data)
{
	if (data->tokens->type == 3 && data->tokens->next == NULL)
	{
		(ft_set_parse_err(data, E_SYNTAX), ft_handle_parse_err(data));
		return;
	}
	ft_init_heroduc(data);
	if (data->heredoc_sigint)
	{
		ft_clear_token_list(&data->tokens);
		data->heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_term);
	data->exit_s = ft_exec_cmd(data, data->tokens, false);
	ft_clear_token_list(&data->tokens);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	((void)argc, (void)argv);
	ft_init_minishell(&data, env);

	while (1)
	{
		signals_init(&data);
		data.line = readline(PROMPT);
		if (!data.line)
			(ft_clean_ms(&data), ft_putstr_fd("aqui exit\n", 1), exit(data.exit_s));
		if (data.line[0])
			add_history(data.line);
		data.tokens = ft_tokenize(&data);
		if (!data.tokens)
			continue ;
		if (data.parse_err.type)
		{
			ft_handle_parse_err(&data);
			continue ;
		}
		ft_start_execution(&data);
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(&data), data.exit_s);
}
