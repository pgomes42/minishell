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
    t_ast *node;

    node = (t_ast *)malloc(sizeof(t_ast));
    if (!node)
        return (perror("Falied to creat ast_node"), NULL);
    node->type = token->type;
    node->value = token->value;
    node->args = token->args;
    node->nb_args = token->nb_args;
    node->argv = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static t_ast *ft_parse_cmd(t_data *data)
{
 t_ast *cmd;


 if (!data->token->type == T_COMAND)
    return (NULL);
cmd = ft_ast_newnode(data->token);
ft_advance_token(data);
return (cmd);    
}

static t_ast *ft_parse_redir(t_data *data, t_ast *cmd)
{
    t_ast *redir;
    t_type type;

    if (data->token->type == T_IN_REDIR || data->token->type == T_OUT_APP_REDIR
        || data->token->type ==T_OUT_SUB_REDIR ||data->token->type == T_HERODUC)
    {
        if (data->tmp->next)
        {
            type =  data->token->type;
           ft_advance_token(data);
            if (data->token->type == T_COMAND)
            {
                redir = ft_ast_newnode(data->token);
                redir->type = type;
            }
            else
               return(ft_parse_error(data, 0), cmd);
            ft_advance_token(data);
            redir->left = cmd;
        }
        else
            return (ft_parse_error(data, 0), cmd);
        cmd = redir;
    }
    return (cmd);    
}

static t_ast *ft_parse_pipe(t_ast *left, t_ast *right)
{
    t_ast *pipe;

    pipe= (t_ast *)malloc(sizeof(t_ast));
    if (!pipe)
        return (perror("Falied to creat ast_node"), NULL);
    pipe->type = T_PIPE;
    pipe->value =NULL;
    pipe->args = NULL;
    pipe->argv = NULL;
    pipe->left = left;
    pipe->right = right;
    return (pipe);
}

t_ast *ft_creat_root(t_data *data)
{
    t_ast *left;
    t_ast *right; 
    
    left = ft_parse_cmd(data);
    if(!left)
        return(NULL);
    left = ft_parse_redir(data, left);
    while(data->token->type == T_PIPE && !data->error->error)
    {
        ft_advance_token(data);
        right = ft_parse_cmd(data);
        if (!right)
            return (ft_parse_error(data, 1), left);
        right = ft_parse_redir(data, right);
        left = ft_parse_pipe(left, right);
        if (!left)
			return (NULL);
    }
   return (left);
}



