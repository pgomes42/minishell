/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:13:04 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:38:58 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path(t_data *data, char *cmd)
{
	char	*value;
	char	**splited;
	int		i;

	i = -1;
	value = NULL;
	if (ft_strchr(cmd, '/') && !access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	splited = ft_split(ft_getenv_value(data->list_env, ft_strdup("PATH")), ':');
	while (splited && splited[++i])
	{
		value = ft_strjoin(splited[i], "/");
		value = ft_strjoin_f(value, strdup(cmd));
		if (!access(value, F_OK | X_OK))
			return (ft_clear_matrix(splited), value);
		free(value);
	}
	if (splited)
		ft_clear_matrix(splited);
	return (NULL);
}

static int	ft_execute_cmd(t_data *data, char **argv)
{
	int		pid;
	int		status;
	char	*path;

	path = ft_get_path(data, argv[0]);
	if (!path)
		return (ft_check_cmd(argv[0]));
	status = 0;
	ft_setup_execution();
	pid = fork();
	if (!pid)
	{
		execve(path, argv, data->argv_env);
		perror(argv[0]);
		if (errno == ENOENT)
			_exit(127);
		if (errno == EACCES)
			_exit(126);
	}
	waitpid(pid, &status, 0);
	(free(path), ft_setup_signals());
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	ft_execute_redir(t_data *data, t_ast *ast)
{
	int	status;
	int	orig_fd;
	int	new_fd;

	if (!ft_load_redir(ast, &new_fd, &orig_fd))
		return (1);
	if (ast->type == T_IN_REDIR && dup2(new_fd, STDIN_FILENO) == -1)
		return (perror("dup1"), close(new_fd), close(orig_fd), 1);
	else if ((ast->type == T_OUT_SUB_REDIR || ast->type == T_OUT_APP_REDIR)
		&& dup2(new_fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(new_fd), close(orig_fd), 1);
	close(new_fd);
	status = ft_execute(data, ast->left);
	if (ast->type == T_IN_REDIR && dup2(orig_fd, STDIN_FILENO) == -1)
		return (perror("dup3"), close(orig_fd), status);
	else if ((ast->type == T_OUT_SUB_REDIR || ast->type == T_OUT_APP_REDIR)
		&& dup2(orig_fd, STDOUT_FILENO) == -1)
		return (perror("dup4"), close(orig_fd), status);
	return (close(orig_fd), status);
}

static int	ft_execute_pipe(t_data *data, t_ast *ast)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		right_status;
	int		left_status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (!pid_left)
	{
		(close(pipe_fd[0]), dup2(pipe_fd[1], STDOUT_FILENO));
		close(pipe_fd[1]);
		exit(ft_execute(data, ast->left));
	}
	pid_right = fork();
	if (!pid_right)
	{
		(close(pipe_fd[1]), dup2(pipe_fd[0], STDIN_FILENO));
		close(pipe_fd[0]);
		exit(ft_execute(data, ast->right));
	}
	(close(pipe_fd[0]), close(pipe_fd[1]));
	(waitpid(pid_left, &left_status, 0), waitpid(pid_right, &right_status, 0));
	return (WEXITSTATUS(right_status));
}

int	ft_execute(t_data *data, t_ast *ast)
{
	if (!ast)
		return (1);
	if (ast->type == T_COMAND && ft_is_builtin(ast->argv[0]))
		data->exit_status = ft_execute_builtins(data, ast->argv);
	else if (ast->type == T_COMAND)
		data->exit_status = ft_execute_cmd(data, ast->argv);
	else if (ast->type == T_PIPE)
		data->exit_status = ft_execute_pipe(data, ast);
	else if (ast->type == T_OUT_SUB_REDIR)
		data->exit_status = ft_execute_redir(data, ast);
	else if (ast->type == T_IN_REDIR)
		data->exit_status = ft_execute_redir(data, ast);
	else if (ast->type == T_OUT_APP_REDIR)
		data->exit_status = ft_execute_redir(data, ast);
	else if (ast->type == T_HERODUC)
	{
		data->exit_status = ft_exec_heroduc(data, ast);
	}
	return (data->exit_status);
}
