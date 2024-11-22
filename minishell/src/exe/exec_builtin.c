/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:40:19 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/20 10:40:20 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(t_data *data, t_token *token)
{
	if (ft_strcmp(token->value, "echo") == 0)
		return (ft_echo(data));
	if (ft_strcmp(token->value, "cd") == 0)
		return (ft_cd(data));
	if (ft_strcmp(token->value, "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(token->value, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(token->value, "export") == 0)
		return (ft_export(data));
	if (ft_strcmp(token->value, "unset") == 0)
		return (ft_unset(data));
	ft_exit(data, &token->value);
	return (ENO_GENERAL);
}

bool	ft_is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd") || !ft_strcmp(arg,
			"exit") || !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}
