/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstwhitflag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:02:59 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:49:25 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_initelemlist(t_file *begin_list)
{
	while (begin_list)
	{
		begin_list->usr = NULL;
		begin_list->grp = NULL;
		begin_list->date = NULL;
		begin_list = begin_list->next;
	}
}

void	ft_inlistdel(t_file *begin_list)
{
	while (begin_list)
	{
		free(begin_list->usr);
		free(begin_list->grp);
		free(begin_list->date);
		begin_list = begin_list->next;
	}
}
