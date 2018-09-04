/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_userecu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:03:38 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:50:39 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ft_puterrors(char *str, char *name, int bol)
{
	if (bol == 1)
		ft_printf("\n%s/%s:\n", str, name);
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (1);
}

static int	ft_checkright(t_file *tmp, char *str)
{
	if (!(tmp->buf_stat.st_mode & S_IRUSR) &&
			!(tmp->buf_stat.st_mode & S_IXUSR))
		return (ft_puterrors(str, tmp->name, 0));
	else if (tmp->type == 4 && !(tmp->buf_stat.st_mode & S_IRUSR))
		return (ft_puterrors(str, tmp->name, 1));
	else if ((tmp->type == 4 && !(tmp->buf_stat.st_mode & S_IXUSR)))
	{
		ft_printf("\n%s/%s:\n", str, tmp->name);
		return (1);
	}
	else if (tmp->type == 0 && !(tmp->buf_stat.st_mode & S_IXGRP) &&
			!(tmp->buf_stat.st_mode & S_IRGRP) &&
				!(tmp->buf_stat.st_mode & S_IWGRP))
		return (ft_puterrors(str, tmp->name, 1));
	else if (tmp->type == 0 && (ft_strcmp("fd", tmp->name)) == 0)
		tmp->type = 4;
	return (0);
}

int			ft_userecu(t_flagl *flag, char *str)
{
	t_file	*begin_list;
	t_file	*tmp;
	char	*path;

	begin_list = ft_readdirflag(flag, str);
	ft_putlist_infol(begin_list, flag);
	tmp = begin_list;
	while (tmp)
	{
		while (flag->flag_a == FALSE && tmp && tmp->name[0] == '.')
			tmp = tmp->next;
		if (tmp && (ft_checkright(tmp, str)) == 0 && tmp->type == 4 &&
				(ft_strcmp(".", tmp->name)) != 0 &&
					(ft_strcmp("..", tmp->name)) != 0)
		{
			path = ft_creatpath(str, tmp, 0);
			ft_printf("\n%s:\n", path);
			ft_userecu(flag, path);
			free(path);
		}
		(tmp) ? tmp = tmp->next : 0;
	}
	ft_inlistdel(begin_list);
	ft_dellist(begin_list);
	return (1);
}
