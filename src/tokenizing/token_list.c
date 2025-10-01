/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:18:37 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/02 14:56:56 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_newtoken(char *value, t_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (perror("Error to creat token\n"), NULL);
	new_token->value = NULL;
	new_token->args = NULL;
	new_token->nb_args = 0;
	if (value)
		new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	ft_addargs_token(t_token *token, char *new_args)
{
	int		i;
	char	**args;

	i = token->nb_args;
	args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!args)
		perror("Erro aqui\n");
	i = 0;
	while (token->args && token->args[i])
	{
		args[i] = token->args[i];
		i++;
	}
	args[i] = new_args;
	args[i + 1] = NULL;
	if (token->args)
		free(token->args);
	token->nb_args++;
	token->args = args;
}

void	clear_token(void *to)
{
	t_token	*token;
	int		i;

	token = (t_token *)to;
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	token->value = NULL;
	i = -1;
	while (token->args && token->args[++i])
		free(token->args[i]);
	if (token->args)
		free(token->args);
	token->args = NULL;
	free(token);
	token = NULL;
}

void	print_token(void *to)
{
	t_token	*token;
	int		i;

	token = (t_token *)to;
	if (!token)
		return ;
	printf("valor : %s$\n", token->value);
	printf("Argumentos: ");
	i = -1;
	while (token->args && token->args[++i])
	{
		printf("[%d] '%s$ ", i, token->args[i]);
	}
	printf("\n");
	printf("token type : %d \n\n\n", token->type);
}

int	ft_add_token(t_data *data, char *value, t_type type)
{
	data->token = ft_newtoken(value, type);
	if (!data->token)
		return (0);
	if (!data->list_token)
		data->list_token = ft_lstnew(data->token);
	else
		ft_lstadd_back(&data->list_token, ft_lstnew(data->token));
	return (1);
}
