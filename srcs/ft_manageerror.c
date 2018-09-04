/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manageerror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:03:29 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:49:42 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_freetab(char **tab_file)
{
	int		i;

	i = 0;
	while (tab_file[i])
	{
		free(tab_file[i]);
		i++;
	}
	free(tab_file);
}

void		ft_mallocfail(DIR *dir, t_file *begin_list, char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	if (dir)
		closedir(dir);
	if (begin_list)
		ft_dellist(begin_list);
	exit(1);
}

int			ft_freeerror(char *usr, char *grp, char *date)
{
	if (usr)
		free(usr);
	if (grp)
		free(grp);
	if (date)
		free(date);
	return (-1);
}

void		ft_freeerrorlst_flag(t_drfl *begin_list, t_flagl *flag)
{
	t_drfl	*tmp;

	while (begin_list)
	{
		tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->name);
		free(tmp);
	}
	free(flag);
	exit(1);
}

void		ft_free_lst_drfl(t_drfl *begin_list, t_flagl *flag)
{
	t_drfl	*tmp;

	while (begin_list)
	{
		tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->name);
		free(tmp);
	}
	(flag) ? free(flag) : 0;
	exit(1);
}
