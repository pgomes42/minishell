/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_appenders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:38:09 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/21 05:43:43 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_separator(t_token_type type, char **line_ptr,
		t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
		(*line_ptr)++;
	return (1);
}

int	ft_append_identifier(t_data *data, char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(data, tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}
t_token	*ft_tokenize(t_data *data)
{
	char *line;
	t_token *token_list;
	t_token *tmp;

	line = data->line;
	token_list = ft_tokenization_handler(data, line);
	tmp = token_list;
	while (tmp)
	{
		if ((tmp->type == T_NL || tmp->type == T_DGREAT || tmp->type == T_PIPE
				|| tmp->type == T_LESS || tmp->type == T_C_PARENT
				|| tmp->type == T_GREAT || tmp->type == T_LESS)
			&& (tmp->next == NULL))
		{
			ft_set_parse_err(data, E_SYNTAX);
		}
		tmp = tmp->next;
	}
	free(line);
	data->line = NULL;
	return (token_list);
}