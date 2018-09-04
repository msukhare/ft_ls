/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_onefile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:29:49 by msukhare          #+#    #+#             */
/*   Updated: 2018/09/04 10:19:06 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ft_printfinfo(t_stat buf, t_flagl *flag, t_drfl *link)
{
	char	*usr;
	char	*grp;
	char	*date;

	usr = ft_getname(buf, 1);
	grp = ft_getname(buf, 2);
	if (!usr || !grp)
		return (ft_freeerror(usr, NULL, NULL));
	if (!(date = ft_getdate(buf.st_mtime)))
		return (ft_freeerror(usr, grp, NULL));
	if ((flag->flag_g || flag->flag_o || flag->flag_l) &&
		((buf.st_mode & S_IFMT) == S_IFLNK) &&
		!(link->name = ft_getlinks(link->name, link->name)))
		return (ft_freeerror(usr, grp, date));
	ft_getright(buf.st_mode, ft_getacl(link->name));
	ft_printf("%hu\t", buf.st_nlink);
	(flag->flag_g == FALSE) ? ft_printf("%s\t", usr) : 0;
	(flag->flag_o == FALSE) ? ft_printf("%s\t", grp) : 0;
	ft_printf("%llu\t", buf.st_size);
	ft_printf("%s\t", date);
	ft_freeerror(usr, grp, date);
	return (0);
}

int			ft_putinfoforfile(t_drfl *link, t_flagl *flag)
{
	t_stat	buf;

	if ((lstat(link->name, &buf)) == -1)
		return (-1);
	if (flag->flag_s)
		ft_printf("%llu  ", buf.st_blocks);
	if (flag->flag_l || flag->flag_g || flag->flag_o)
	{
		if ((ft_printfinfo(buf, flag, link)) == -1)
			return (-1);
	}
	ft_printf("%s\n", link->name);
	return (0);
}

int			ft_printffiles(t_drfl *begin_list, t_flagl *flag, int size)
{
	int		bksh;

	bksh = 0;
	while (begin_list)
	{
		if (begin_list->val == 1 && !flag)
			ft_printf("%s\n", begin_list->name);
		else if ((begin_list->val == 1 || (begin_list->val != 2 &&
				((begin_list->st_mode & S_IFMT) == S_IFLNK))) && flag)
		{
			if (begin_list->val == 0)
			{
				size--;
				begin_list->val = 1;
			}
			if ((ft_putinfoforfile(begin_list, flag)) == -1)
				return (-1);
		}
		(bksh == 0 && begin_list->val == 1) ? bksh = 1 : 0;
		begin_list = begin_list->next;
	}
	(bksh == 1 && size >= 1) ? ft_putchar('\n') : 0;
	return (0);
}
