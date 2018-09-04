/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:30:20 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:50:15 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_swaplinks(t_file *p, t_file *q)
{
	t_file		*tmp;

	tmp = q->next;
	q->next = tmp->next;
	tmp->next = p->next;
	p->next = tmp;
}

t_file			*ft_helpformerge(int scmed, t_file *sp_l)
{
	while (scmed >= 1 && sp_l)
	{
		sp_l = sp_l->next;
		scmed--;
	}
	return (sp_l);
}

static t_file	*ft_merge(t_file *bg_lst, int med, t_file *sp_l, int scmed)
{
	int			size;
	int			i;

	i = 0;
	size = (ft_lstlen(bg_lst) - 1);
	while (i <= size && bg_lst)
	{
		if (bg_lst->next && sp_l->next &&
			bg_lst->next->buf_stat.st_mtime < sp_l->next->buf_stat.st_mtime)
		{
			ft_swaplinks(bg_lst, sp_l);
			if (scmed == 1)
				break ;
			scmed--;
		}
		else
		{
			if (med == 1 && sp_l)
				return (ft_helpformerge(scmed, sp_l));
			med--;
		}
		bg_lst = bg_lst->next;
		i++;
	}
	return (sp_l);
}

static t_file	*ft_inmerge(t_file *bg_lst, int med, t_file *sp_l, int scmed)
{
	int			size;
	int			i;

	i = 0;
	size = (ft_lstlen(bg_lst) - 1);
	while (i <= size && bg_lst)
	{
		if (bg_lst->next && sp_l->next &&
			bg_lst->next->buf_stat.st_mtime > sp_l->next->buf_stat.st_mtime)
		{
			ft_swaplinks(bg_lst, sp_l);
			if (scmed == 1)
				break ;
			scmed--;
		}
		else
		{
			if (med == 1 && sp_l)
				return (ft_helpformerge(scmed, sp_l));
			med--;
		}
		bg_lst = bg_lst->next;
		i++;
	}
	return (sp_l);
}

t_file			*ft_sort(t_file *bg_lst, int n, int order)
{
	int			mediane;
	int			spl_med;
	t_file		*to_ret;

	mediane = (n / 2);
	spl_med = (n - mediane);
	if (spl_med >= 2)
	{
		to_ret = ft_sort(bg_lst, spl_med, order);
		if (mediane >= 2)
			ft_sort(to_ret, mediane, order);
	}
	else if (bg_lst)
		to_ret = bg_lst->next;
	if (order == 1)
		to_ret = ft_merge(bg_lst, spl_med, to_ret, mediane);
	else
		to_ret = ft_inmerge(bg_lst, spl_med, to_ret, mediane);
	return (to_ret);
}
