/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 11:19:52 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 16:09:43 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ft_useflag_onpoint(char **tab_flag)
{
	t_file	*begin_list;
	t_flagl	*flag;

	flag = ft_getflagl(tab_flag);
	if (flag->flag_recu == TRUE)
		ft_userecu(flag, ".");
	else
	{
		begin_list = ft_readdirflag(flag, ".");
		ft_putlist_infol(begin_list, flag);
	}
	free(flag);
}

int			main(int argc, char **argv)
{
	char	**tab_flag;
	char	**tab_file;
	t_file	*begin_list;

	tab_flag = NULL;
	tab_file = NULL;
	if (argc <= 1)
	{
		begin_list = ft_readdir(".");
		ft_sortlistfile(begin_list, 1);
		ft_putlist(begin_list);
		return (0);
	}
	ft_getintab(argc, argv, &tab_flag, &tab_file);
	if (tab_file && !tab_flag)
		ft_readdirs(tab_file);
	else if (tab_flag && !tab_file)
		ft_useflag_onpoint(tab_flag);
	else if (tab_flag && tab_file)
		ft_displayfilesflag(tab_flag, tab_file);
	return (0);
}
