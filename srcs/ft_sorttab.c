/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:33:24 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:50:31 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ft_swpelems(t_file *tmp, t_file *link)
{
	int		type;
	char	*help;

	help = tmp->name;
	tmp->name = link->name;
	link->name = help;
	type = tmp->type;
	tmp->type = link->type;
	link->type = type;
}

void		ft_sortlistfile(t_file *begin_list, int order)
{
	t_file	*tmp;
	t_file	*index;

	while (begin_list)
	{
		tmp = begin_list;
		index = tmp;
		while (tmp)
		{
			if (order == 1 && (ft_strcmp(index->name, tmp->name)) > 0)
				index = tmp;
			else if (order == 2 && (ft_strcmp(index->name, tmp->name)) < 0)
				index = tmp;
			tmp = tmp->next;
		}
		ft_swpelems(begin_list, index);
		begin_list = begin_list->next;
	}
}

void		ft_sorttabfile(char **tab_file, int order)
{
	int		i;
	int		j;
	int		index;
	char	*tmp;

	i = 0;
	while (tab_file[i])
	{
		j = i;
		index = i;
		while (tab_file[j])
		{
			if (order == 1 && (ft_strcmp(tab_file[index], tab_file[j])) > 0)
				index = j;
			if (order == 2 && (ft_strcmp(tab_file[index], tab_file[j])) < 0)
				index = j;
			j++;
		}
		tmp = tab_file[index];
		tab_file[index] = tab_file[i];
		tab_file[i] = tmp;
		i++;
	}
}

int			ft_lstlen(t_file *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}
