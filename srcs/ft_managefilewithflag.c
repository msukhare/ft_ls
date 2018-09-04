/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_managefilewithflag.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:47:00 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 15:49:36 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ft_getinfol(char *path, t_file *link, t_flagl *flag)
{
	t_stat	buf;

	lstat(path, &buf);
	if (!(link->usr = ft_getname(buf, 1)))
		return (-1);
	if (!(link->grp = ft_getname(buf, 2)))
		return (-1);
	link->buf_stat.st_mode = buf.st_mode;
	link->buf_stat.st_nlink = buf.st_nlink;
	link->buf_stat.st_size = buf.st_size;
	link->buf_stat.st_blocks = buf.st_blocks;
	link->buf_stat.st_mtime = buf.st_mtime;
	link->buf_stat.st_rdev = buf.st_rdev;
	if (!(link->date = ft_getdate(buf.st_mtime)))
		return (-1);
	if ((flag->flag_g || flag->flag_o || flag->flag_l) &&
		((link->buf_stat.st_mode & S_IFMT) == S_IFLNK) &&
			!(link->name = ft_getlinks(link->name, path)))
		return (-1);
	link->acl = ft_getacl(path);
	return (0);
}

int			ft_managel(t_flagl *flag, t_file *bg_lst, char *str)
{
	t_file	*tmp;
	char	*path;

	ft_initelemlist(bg_lst);
	tmp = bg_lst;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if (!(path = ft_creatpath(str, tmp, 1)))
				return (-1);
		}
		else if (!(path = ft_creatpath(str, tmp, 0)))
			return (-1);
		if (!path)
			return (-1);
		if ((ft_getinfol(path, tmp, flag)) == -1)
		{
			free(path);
			return (-1);
		}
		free(path);
		tmp = tmp->next;
	}
	return (0);
}

void		ft_putlist_infol(t_file *begin_list, t_flagl *flag)
{
	t_file	*link;

	link = begin_list;
	if (flag->flag_l || flag->flag_o || flag->flag_g || flag->flag_s)
		ft_getsizeblocks(begin_list, flag);
	while (link)
	{
		while (flag->flag_a == FALSE && link && link->name[0] == '.')
			link = link->next;
		if (link)
		{
			(flag->flag_s) ? ft_printf("%llu  ", link->buf_stat.st_blocks) : 0;
			if (flag->flag_l || flag->flag_o || flag->flag_g)
				ft_putinfol(link, flag);
			ft_printf("%s\n", link->name);
			link = link->next;
		}
	}
	if (flag->flag_recu == FALSE)
	{
		ft_inlistdel(begin_list);
		ft_dellist(begin_list);
	}
}

t_file		*ft_readdirflag(t_flagl *flag, char *str)
{
	t_file	*begin_list;

	begin_list = ft_readdir(str);
	if (flag->flag_r && flag->flag_f == FALSE)
		ft_sortlistfile(begin_list, 2);
	else
		ft_sortlistfile(begin_list, 1);
	if ((ft_managel(flag, begin_list, str)) == -1)
	{
		ft_inlistdel(begin_list);
		free(flag);
		ft_mallocfail(NULL, begin_list, NULL);
		return (NULL);
	}
	if (flag->flag_t && flag->flag_r && flag->flag_f == FALSE)
		ft_sort(begin_list, ft_lstlen(begin_list), 2);
	else if (flag->flag_t && flag->flag_f == FALSE)
		ft_sort(begin_list, ft_lstlen(begin_list), 1);
	return (begin_list);
}
