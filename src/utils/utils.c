/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:28:28 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:40:46 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error_msg(t_data *data)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd(data->error->msg, 2);
	ft_putstr_fd("\n", 2);
	data->error->error = false;
}
