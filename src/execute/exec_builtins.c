/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:51:20 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/24 14:36:56 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd,
			"env"));
}

int	ft_execute_builtins(t_data *data, char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(data, argv));
	else if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(data, argv[1]));
	else if (!ft_strcmp(argv[0], "export"))
		return (ft_export(data, argv));
	else if (!ft_strcmp(argv[0], "env"))
		return (ft_lstiter(data->list_env, &print_env), 0);
	else if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(data, argv));
	return (1);
}
