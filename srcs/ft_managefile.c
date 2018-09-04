/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_managefile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:47:48 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/12 15:05:08 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ft_puterror(t_drfl *tmp)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(tmp->name, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	tmp->val = 2;
}

int			ft_checkfile(t_drfl *begin_list)
{
	int		size;
	DIR		*dir;
	t_drfl	*tmp;

	size = 0;
	tmp = begin_list;
	errno = 0;
	while (tmp)
	{
		if (!(dir = opendir(tmp->name)) && errno != ENOTDIR)
			ft_puterror(tmp);
		else if (dir)
		{
			closedir(dir);
			size++;
		}
		else
			tmp->val = 1;
		tmp = tmp->next;
	}
	return (size);
}

t_file		*ft_readdir(char *str)
{
	t_file	*begin_list;
	t_file	*tmp;
	t_dir	*file;
	DIR		*dir;

	if (!(dir = opendir(str)))
		return (NULL);
	file = readdir(dir);
	if (!(begin_list = ft_createlem(file->d_name, file->d_type)))
		ft_mallocfail(dir, NULL, NULL);
	tmp = begin_list;
	while ((file = readdir(dir)))
	{
		if (!(tmp->next = ft_createlem(file->d_name, file->d_type)))
			ft_mallocfail(dir, begin_list, NULL);
		tmp = tmp->next;
	}
	closedir(dir);
	ft_sortlistfile(begin_list, 1);
	return (begin_list);
}

void		ft_readlist(t_drfl *begin_list, int size, t_flagl *flag)
{
	int		i;
	t_drfl	*tmp;

	if ((ft_printffiles(begin_list, flag, size)) == -1)
		ft_freeerrorlst_flag(begin_list, flag);
	tmp = begin_list;
	i = size;
	while (tmp)
	{
		if (tmp->val == 0)
		{
			(i >= 2 && (!flag || (flag && flag->flag_recu == FALSE))) ?\
				ft_printf("%s:\n", tmp->name) : 0;
			if (!flag && (tmp->st_mode & S_IXUSR))
				ft_putlist(ft_readdir(tmp->name));
			else if (flag && (flag->flag_recu) && (tmp->st_mode & S_IRUSR) &&
					(tmp->st_mode & S_IXUSR))
				ft_userecu(flag, tmp->name);
			else if ((tmp->st_mode & S_IRUSR) && (tmp->st_mode & S_IXUSR))
				ft_putlist_infol(ft_readdirflag(flag, tmp->name), flag);
			(--size > 0) ? ft_putchar('\n') : 0;
		}
		tmp = tmp->next;
	}
}

void		ft_readdirs(char **tab_file)
{
	t_drfl	*begin_list;
	t_drfl	*tmp;
	int		size;

	ft_sorttabfile(tab_file, 1);
	begin_list = ft_splitlst(tab_file);
	size = ft_checkfile(begin_list);
	if ((ft_checkinfo(begin_list)) == -1)
		ft_free_lst_drfl(begin_list, NULL);
	ft_readlist(begin_list, size, NULL);
	while (begin_list)
	{
		tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->name);
		free(tmp);
	}
}
