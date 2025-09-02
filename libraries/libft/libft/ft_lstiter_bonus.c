/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:28 by pgomes            #+#    #+#             */
/*   Updated: 2025/08/30 16:18:10 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*list_ptr;
	if (!lst)
		return ;
	list_ptr = lst;
	
	while (list_ptr != NULL)
	{
		(*f)(list_ptr->content);
		list_ptr = list_ptr->next;
	}
}
