/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:05:35 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/17 10:06:36 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_check_cmd(char *file)
{
    if (ft_strchr(file, '/'))
    {
        if (access(file, F_OK) == 0 && access(file, X_OK) != 0)
            return (perror(file), 126);
        return (perror(file), 127);
    }
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": command not found\n", 2);
    return (127);
}

int ft_load_redir(t_ast *ast, int *new_fd, int *orig_fd)
{
    if (ast->type == T_IN_REDIR)
        *new_fd = open(ast->value, O_RDONLY);
    else if (ast->type == T_OUT_SUB_REDIR)
        *new_fd = open(ast->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else
        *new_fd = open(ast->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*new_fd < 0)
        return (perror(ast->value), 0);
    if (ast->type == T_IN_REDIR)
        *orig_fd = dup(STDIN_FILENO);
    else
        *orig_fd = dup(STDOUT_FILENO);
    if (*orig_fd < 0)
        return (perror("dup"), close(*new_fd), 0);
    return (1);
}

int ft_exec_heroduc(t_data *data, t_ast *ast)
{
    int pid;
    int status;
    char *line;
    int pipe_fd[2];

    (pipe(pipe_fd), pid = fork());
    if (pid == 0)
    {
        close(pipe_fd[0]);
        while (1)
        {
            line = readline("> ");
            if (!line || !ft_strcmp(line, ast->value))
            {
                free(line);
                break ;
            }
        ft_putstr_fd(line, pipe_fd[1]);
        ft_putstr_fd("\n", pipe_fd[1]);
        free(line);
        }
        (close(pipe_fd[1]), _exit(0));
    }
    waitpid(pid, &status, 0);
     close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
        //return (perror("dup"), close(pipe_fd[0]), 1);
    close(pipe_fd[0]);
    status = ft_execute(data, ast->left);
    //if (WIFSIGNALED(status))
      //  return (128 + WTERMSIG(status));
    return (WEXITSTATUS(status));
}   
