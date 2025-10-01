/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:13:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:50:36 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_ast(t_ast **root)
{
	if (!(*root))
		return ;
	ft_clear_ast(&(*root)->left);
	ft_clear_ast(&(*root)->right);
	ft_clear_matrix((*root)->argv);
	free(*root);
	*root = NULL;
}

void	ft_advance_token(t_data *data)
{
	if (!data->tmp->next)
		return ;
	data->tmp = data->tmp->next;
	data->token = (t_token *)data->tmp->content;
}

void	ft_parse_error(t_data *data, int type)
{
	if (type == 0)
		data->error->msg = "expected filename after redirection";
	else if (type == 1)
		data->error->msg = "expected command after pipe";
	else if (type == 2)
		data->error->msg = "expected \"";
	data->error->error = true;
}
