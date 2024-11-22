/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:40:31 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/20 10:40:32 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_out(t_token *current_token, int *status)
{
	int	fd;

	current_token = current_token->next;
	if (!current_token)
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				current_token->value});
		return (*status);
	}
	fd = open(current_token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(current_token->value));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_in(t_token *current_token, int *status)
{
	int	fd;

	current_token = current_token->next;
	if (!current_token)
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				current_token->value});
		return (*status);
	}
	fd = open(current_token->value, O_RDONLY);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_read(current_token->value));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_append(t_token *current_token, int *status)
{
	int	fd;

	current_token = current_token->next;
	if (!current_token->value)
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				current_token->value});
		return (*status);
	}
	fd = open(current_token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(current_token->value));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
