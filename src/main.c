/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:36:38 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:34:54 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_token_ast(t_data *data)
{
	t_ast	*root;

	// Validate input data structure
	if (!data || !data->list_token)
		return (0);
	data->tmp = data->list_token;
	data->token = (t_token *)data->tmp->content;
	if (data->token->type == T_PIPE)
		return (ft_putstr_fd("minishell: syntax error: near unexpected `|'\n",
				2), 0);
	// Initialize error handling state
	data->error->error = false;
	data->error->msg = NULL;
	// Build Abstract Syntax Tree from token list
	root = ft_creat_root(data);
	if (data->error->error)
	{
		// Display syntax error message to stderr
		ft_putstr_fd("minishell: syntax error: ", 2);
		ft_putstr_fd(data->error->msg, 2);
		ft_putstr_fd("\n", 2);
		if (root)
			ft_clear_ast(&root);
		return (0);
	}
	data->ast = root;
	return (1);
}

static void	ft_exit1(t_data *data)
{
	if (data->error)
		free(data->error);
	ft_lstclear(&data->list_env, &clear_env);
	ft_lstclear(&data->list_token, &clear_token);
	free(data->line);
	exit(data->exit_status);
}

static void	ft_reload(t_data *data)
{
	ft_clear_ast(&data->ast);
	ft_lstclear(&data->list_token, &clear_token);
	ft_clear_matrix(data->argv_env);
	data->argv_env = NULL;
	free(data->line);
	data->line = NULL;
	data->token = NULL;
	data->tmp = NULL;
}

static void	ft_init(t_data *data, char **env)
{
	ft_extract_env(data, env);
	data->error = malloc(sizeof(t_error));
	data->error->error = false;
	data->exit_status = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	(void)argv, (void)argc;
	ft_memset(&data, 0, sizeof(data));
	(ft_disable_ctrl_echo(), ft_setup_signals());
	ft_init(&data, env);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (data.line)
		{
			if (ft_is_empty(data.line))
				continue ;
			(add_history(data.line), ft_tokenizing(&data, data.line));
			if (data.error->error)
				(ft_print_error_msg(&data), ft_reload(&data));
			else if (ft_parse_token_ast(&data))
				(ft_load_ats_argv(&data, data.ast), ft_load_env_argv(&data),
					ft_execute(&data, data.ast));
			ft_reload(&data);
		}
		else if (!data.line)
			ft_exit1(&data);
	}
	return (0);
}
