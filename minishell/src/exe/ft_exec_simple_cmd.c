/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:45:38 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/21 06:54:15 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redirection(t_data *data)
{
	t_token	*tmp;
	int		tmp_status;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == 2 && ft_out(tmp, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp->type == 1 && ft_in(tmp, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp->type == 4 && ft_append(tmp, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp->type == 3)
			(dup2(data->here_doc, 0), close(data->here_doc));
		tmp = tmp->next;
	}
	return (ENO_SUCCESS);
}

void	ft_reset_stds(t_data *data, bool piped)
{
	if (piped)
		return ;
	dup2(data->stdin, 0);
	dup2(data->stdout, 1);
}

char	**ft_expand_args(t_data *data, t_token *current_token)
{
	t_token	*current;
	int		count;
	char	**argv;

	count = 0;
	current = current_token;
	while (current != NULL && current->type == T_IDENTIFIER)
	{
		count++;
		current = current->next;
	}
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	current = current_token;
	count = -1;
	while (current != NULL && current->type == T_IDENTIFIER)
	{
		argv[++count] = ft_garbage_collector(ft_strdup((ft_expand(data,
							current->value)[0])), false);
		if (argv[count] == NULL)
			(ft_free_char2(argv), ft_clean_ms(data), exit(ENO_GENERAL));
		current = current->next;
	}
	argv[++count] = NULL;
	data->expanded_args = argv;
	return (argv);
}

static int	ft_exec_child(t_data *data, t_token *current_token, int tmp_status)
{
	char	**argv;
	t_path	path_status;
	int		fork_pid;

	data->signint_child = true;
	argv = ft_expand_args(data, current_token);
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = ft_check_redirection(data);
		if (tmp_status != ENO_SUCCESS)
			(ft_clean_ms(data), ft_free_char2(argv), exit(ENO_GENERAL));
		path_status = ft_get_path(data, (current_token->value));
		if (path_status.err.no != ENO_SUCCESS)
		{
			tmp_status = ft_err_msg(path_status.err);
			(ft_clean_ms(data), ft_free_char2(argv), exit(tmp_status));
		}
		if (execve(path_status.path, argv, data->environ) == -1)
			(ft_clean_ms(data), ft_free_char2(argv), exit(1));
	}
	data->signint_child = (waitpid(fork_pid, &tmp_status, 0), false);
	if (WIFSIGNALED(tmp_status))
		return (128 + WTERMSIG(tmp_status));
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_simple_cmd(t_data *data, t_token *current_token, bool piped)
{
	int	tmp_status;

	tmp_status = 0;
	if (!current_token->value)
	{
		tmp_status = ft_check_redirection(data);
		return (ft_reset_stds(data, piped), (tmp_status && ENO_GENERAL));
	}
	else if (ft_is_builtin((current_token->value)))
	{
		tmp_status = ft_check_redirection(data);
		if (tmp_status != ENO_SUCCESS)
			return (ft_reset_stds(data, piped), ENO_GENERAL);
		tmp_status = ft_exec_builtin(data, current_token);
		return (ft_reset_stds(data, piped), tmp_status);
	}
	else
		return (ft_exec_child(data, current_token, tmp_status));
}
