/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displayfilesflag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 11:20:32 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:48:30 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ft_checkinfo(t_drfl *begin_list)
{
	t_stat	buf;

	while (begin_list)
	{
		if (begin_list->val != 2)
		{
			if ((lstat(begin_list->name, &buf)) == -1)
				return (-1);
			begin_list->st_mode = buf.st_mode;
			begin_list->time = buf.st_mtime;
		}
		begin_list = begin_list->next;
	}
	return (0);
}

void		ft_helpswp(t_drfl *index, t_drfl *to_swp)
{
	char	*tmp_name;
	int		tmp_val;
	mode_t	tmp_mode;
	time_t	tmp_time;

	tmp_name = index->name;
	index->name = to_swp->name;
	to_swp->name = tmp_name;
	tmp_val = index->val;
	index->val = to_swp->val;
	to_swp->val = tmp_val;
	tmp_mode = index->st_mode;
	index->st_mode = to_swp->st_mode;
	to_swp->st_mode = tmp_mode;
	tmp_time = index->time;
	index->time = to_swp->time;
	to_swp->time = tmp_time;
}

void		ft_stdrfl(t_drfl *begin_list, int order)
{
	t_drfl	*tmp;
	t_drfl	*index;

	while (begin_list)
	{
		tmp = begin_list;
		index = begin_list;
		while (tmp)
		{
			if (order == 1 && tmp->val != 2 && index->time < tmp->time)
				index = tmp;
			else if (order == 2 && tmp->val != 2 && index->time > tmp->time)
				index = tmp;
			tmp = tmp->next;
		}
		ft_helpswp(index, begin_list);
		begin_list = begin_list->next;
	}
}

void		ft_displayfilesflag(char **tab_flag, char **tab_files)
{
	t_flagl	*flag;
	t_drfl	*begin_list;
	t_drfl	*tmp;
	int		size;

	flag = ft_getflagl(tab_flag);
	(flag->flag_r && flag->flag_f == FALSE) ? ft_sorttabfile(tab_files, 2)\
			: ft_sorttabfile(tab_files, 1);
	begin_list = ft_splitlst(tab_files);
	size = ft_checkfile(begin_list);
	if ((ft_checkinfo(begin_list)) == -1)
		ft_free_lst_drfl(begin_list, flag);
	if (flag->flag_t && flag->flag_f == FALSE)
		(flag->flag_r) ? ft_stdrfl(begin_list, 2) : ft_stdrfl(begin_list, 1);
	ft_readlist(begin_list, size, flag);
	while (begin_list)
	{
		tmp = begin_list;
		free(begin_list->name);
		begin_list = begin_list->next;
		free(tmp);
	}
	free(flag);
}
