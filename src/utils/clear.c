/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:02:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/14 19:05:02 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_clear_matrix(char **matrix)
{
    int i;

    i = -1;
    while (matrix && matrix[++i])
        free(matrix[i]);
    if (matrix)
        free(matrix);
}