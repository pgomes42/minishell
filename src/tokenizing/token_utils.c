/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:51:57 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/01 21:14:50 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isquote(char c)
{
    return (c == '\'' || c == '"');
}

int ft_isseparator(char c)
{
    return ( c == ' ' || c == '\t' || c == '('
        || c == ')' || c == ')' || c == '<'
        || c == '>' || c == '|' || c == '&'       
    );
}
int ft_skipspace(char *str, int *i)
{    
    while(str && str[*i] != '\0' && ft_isspace(str[*i]))
        (*i)++;
    return (*i);
}
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int is_redir_or_pipe(char c)
{
    return (c == '<' || c == '>' || c == '|');
}

