/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:51:57 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:39:52 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isseparator(char c)
{
	return (c == ' ' || c == '\t' || c == '(' || c == ')' || c == ')'
		|| c == '<' || c == '>' || c == '|' || c == '&');
}

void	ft_skipspace(char **str)
{
	while (str && ft_isspace(**str))
		(*str)++;
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	is_redir_or_pipe(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
