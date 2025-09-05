/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:40:04 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/05 13:13:13 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast *ft_ast_newnode(t_token *token)
{
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
    if (!node)
        return (perror("Falied to creat ast_node"), NULL);
    node->type = token->type;
    node->value = token->value;
    node->args = token->args;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void parse_cmd(t_ast **root, t_ast **last_cmd, t_token *token)
{
    t_ast *cmd_node = ft_ast_newnode(token);
    if (!*root)
        *root = cmd_node;
    if (*last_cmd)
        (*last_cmd)->right = cmd_node;
    *last_cmd = cmd_node;
}

static void parse_pipe(t_ast **root, t_ast **last_cmd, t_token *token)
{
    t_ast *pipe_node = ft_ast_newnode(token);
    if (*root)
    {
        pipe_node->left = *root;
        *root = pipe_node;
    }
    *last_cmd = NULL;
}

static void parse_redir(t_ast **last_cmd, t_token *token)
{
    t_ast *redir_node = ft_ast_newnode(token);
    if (*last_cmd)
    {
        if ((*last_cmd)->right)
            (*last_cmd)->right->right = redir_node;
        else
            (*last_cmd)->right = redir_node;
    }
}


void ft_parse_token_ast(t_data *data)
{
    t_list *curr = data->list_token;
    t_ast *root = NULL;
    t_ast *last_cmd = NULL;
    t_token *token;

    while (curr)
    {
        token = (t_token *)curr->content;
        if (token->type == T_COMAND)
            parse_cmd(&root, &last_cmd, token);
        else if (token->type == T_PIPE)
            parse_pipe(&root, &last_cmd, token);
        else if (token->type == T_IN_REDIR || token->type == T_OUT_APP_REDIR
             || token->type == T_OUT_SUB_REDIR || token->type == T_HERODUC)
            parse_redir(&last_cmd, token);
        curr = curr->next;
    }
    data->ast = root;
}
