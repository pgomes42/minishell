/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgonga4242 <sgonga4242@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:40:52 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:54:05 by sgonga4242       ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void ft_add_tokens_collect(t_token **cmd_tokens, t_token **current)
{
	while (*current != NULL && (*current)->type != T_PIPE)
	{
		t_token *new_token = ft_new_token((*current)->value, (*current)->type);
		if (new_token == NULL)
			exit(1);
		ft_token_list_add_back(cmd_tokens, new_token);
		*current = (*current)->next;
	}
}

int create_pipe(int pipes[2][2], int i)
{
	if (pipe(pipes[i % 2]) == -1)
	{
		perror("error pipe\n");
		return 1;
	}
	return 0;
}

void handle_child_process(t_data *data, t_token *cmd_tokens, int pipes[2][2], int i, t_token *current)
{
	if (i > 0)
		dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
	if (current != NULL && current->next != NULL)
		dup2(pipes[i % 2][1], STDOUT_FILENO);
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	ft_exec_cmd(data, cmd_tokens, true);
	exit(0);
}

void handle_parent_process(int pipes[2][2], int i, t_token *current)
{
	if (i > 0)
		close(pipes[(i - 1) % 2][0]);
	if (current != NULL && current->next != NULL)
		close(pipes[i % 2][1]);
}

static int ft_create_pipe_or_isNull(t_token **current, int pipes[2][2], int i, bool task)
{
	if (task)
	{
		if (*current != NULL && (*current)->next != NULL)
		{
			if (create_pipe(pipes, i) != 0)
				return 1;
		}
	}
	else
	{
		if (*current == NULL || (*current)->next == NULL)
			*current = NULL;
		else
			*current = (*current)->next;
	}
	return 0;
}

void ft_await_all_child(int *i, int *status)
{
	while (*i-- > 0)
		wait(status);
}

int ft_exec_pipeline(t_data *data, t_token *current, int status, int i)
{
	int pipes[2][2];
	int pid;

	t_token *cmd_tokens = NULL;
	if (current == NULL)
		return (ENO_SUCCESS);

	while (current != NULL)
	{
		ft_add_tokens_collect(&cmd_tokens, &current);
		if (ft_create_pipe_or_isNull(&current, pipes, i, true))
			return 1;
		data->signint_child = true;
		if ((pid = fork()) == 0)
			handle_child_process(data, cmd_tokens, pipes, i, current);
		else
		{
			handle_parent_process(pipes, i, current);
			cmd_tokens = NULL;
			i++;
		}
		ft_create_pipe_or_isNull(&current, pipes, i, false);
	}
	ft_await_all_child(&i, &status);
	data->signint_child = false;
	return (ft_get_exit_status(status));
}

bool ft_is_pepiline(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == T_PIPE)
			return (true);
		current = current->next;
	}
	return (false);
}

int ft_exec_cmd(t_data *data, t_token *current, bool piped)
{
	if (!current)
		return (130);
	if (ft_is_pepiline(current))
		return (ft_exec_pipeline(data, current, 0, 0));
	else
		return (ft_exec_simple_cmd(data, current, piped));
	return (ENO_GENERAL);
}
