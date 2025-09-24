/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:28 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/24 14:35:08 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(char *argv[])
{
    int i;
    int j;

    i = 0;
    j = -2;
    while (argv[++i])
    {
        if (i == 1 && argv[1][0] == '-' && argv[1][1] == 'n')
        {
            j = 2;
            while (argv[1][j] != '\0' && argv[1][j] == 'n')
                j++;
            if(argv[1][j] == '\0')
            {
                j = -1;
                continue;
            }
        }
        printf("%s", argv[i]);
        if(argv[i + 1])
            printf(" ");
    }
    if (j != -1)
        printf("\n");
    return (0);
}
