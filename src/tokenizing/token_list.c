/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:18:37 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/01 23:10:57 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *ft_newtoken(char *value, t_type type)
{
    t_token *new_token;

    new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = NULL;
    new_token->args = NULL;
    if (value)
        new_token->value = ft_strdup(value);
    
    new_token->type = type;
    return (new_token);
    
}
void ft_addargs_token(t_token *token, char *new_args)
{
    int i;
    char **args;

    i = 0;
    while (token->args && token->args[i])
        i++;
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
    free(token->args);
    token->args = args;
    
}
void clear_token(void *to)
{
    t_token *token;
    
    token = (t_token *)to;
    if(!token)
        return;
    if(token->value)
        free(token->value);
    if(token->args)
        free(token->args);
    free(token);
}

void print_token(void *to)
{
    t_token *token;
    int i;
    
    token = (t_token *)to;
   
    if (!token)
        return ;
    printf("valor : %s \n", token->value);
    printf("Argumentos:\n");
    i = -1;
    while (token->args && token->args[++i])
        printf("[%d] %s ", i, token->args[i]);
    printf("\n");
    printf("token type : %d \n\n\n", token->type);
    
}

int ft_add_token(t_data *data, char *value, t_type type)
{  
    data->token = ft_newtoken(value, type);
    if(!data->token)
        return (perror("Error to creat token\n"), 0);
    if(!data->list_token)
       data->list_token = ft_lstnew(data->token);
    else
      ft_lstadd_back(&data->list_token, ft_lstnew(data->token));
    
    return (1);
}
