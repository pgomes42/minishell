/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:40:04 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/04 22:01:10 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast *ft_newnode(char *value, char **args, t_type type)
{
    t_ast *ast;
    
    ast =(t_ast *)malloc(sizeof(t_ast));
    if (!ast)
        return(perror("Falied to creat ast_node"), NULL);
    ast->args = args;
    ast->value = value;
    ast->type = type;
    ast->left = NULL;
    ast->right = NULL;
    return (ast);    
}

void ft_parse_token_ast(t_data *data)
{
    t_list *list_token;
    t_token *token;

    list_token = data->list_token;
    while(list_token)
    {
        token = (t_token *)list_token->content;
    if(!data->ast)
        data->ast = ft_newnode(token->value, token->args, token->type);
        list_token = list_token->next;
    }
    ft_lstclear(&list_token, &clear_token_other);
}
