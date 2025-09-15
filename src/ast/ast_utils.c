/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:13:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/05 13:13:55 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_ast_node(t_ast *node, int level)
{
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("[type: %d] value: %s\n", node->type, node->value ? node->value : "(null)");
    if (node->args)
    {
        for (int i = 0; node->args[i]; i++)
        {
            for (int j = 0; j < level + 1; j++)
                printf("  ");
            printf("arg[%d]: %s\n", i, node->args[i]);
        }
    }
    if (node->left)
    {
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("left:\n");
        print_ast_node(node->left, level + 2);
    }
    if (node->right)
    {
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("right:\n");
        print_ast_node(node->right, level + 2);
    }
}

void ft_clear_ast(t_ast **root)
{
    if (!(*root))
        return ;
    ft_clear_ast(&(*root)->left);
    ft_clear_ast(&(*root)->right);
    ft_clear_matrix((*root)->argv);
    free(*root);
    *root = NULL;
}
void print_ast(t_ast *root)
{
    printf("AST:\n");
    print_ast_node(root, 0);
}

void ft_advance_token(t_data *data)
{
    if(!data->tmp->next)
        return ;
    data->tmp = data->tmp->next;
    data->token = (t_token *)data->tmp->content;
}
void ft_parse_error(t_data *data, int type)
{
    if(type == 0)
        data->error->msg = "expected filename after redirection";  
    else if (type == 1)
        data->error->msg = "expected command after pipe";
    else if (type == 2)
        data->error->msg = "expected \"";
    data->error->error = true;
}
