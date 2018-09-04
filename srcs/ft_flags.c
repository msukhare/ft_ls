/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:28:47 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 15:33:01 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_flagl	*ft_creatflag(void)
{
	t_flagl		*new_flag;

	if (!(new_flag = (t_flagl*)malloc(sizeof(t_flagl) * 1)))
		return (NULL);
	new_flag->flag_recu = FALSE;
	new_flag->flag_l = FALSE;
	new_flag->flag_a = FALSE;
	new_flag->flag_r = FALSE;
	new_flag->flag_t = FALSE;
	new_flag->flag_g = FALSE;
	new_flag->flag_s = FALSE;
	new_flag->flag_uno = FALSE;
	new_flag->flag_f = FALSE;
	new_flag->flag_o = FALSE;
	return (new_flag);
}

static int		ft_checkflag(char c, t_flagl *flag)
{
	if (c == 'R')
		flag->flag_recu = TRUE;
	else if (c == 'l')
		flag->flag_l = TRUE;
	else if (c == 'a')
		flag->flag_a = TRUE;
	else if (c == 'r')
		flag->flag_r = TRUE;
	else if (c == 't')
		flag->flag_t = TRUE;
	else if (c == 'g')
		flag->flag_g = TRUE;
	else if (c == 's')
		flag->flag_s = TRUE;
	else if (c == '1')
		flag->flag_uno = TRUE;
	else if (c == 'o')
		flag->flag_o = TRUE;
	else if (c == 'f')
		flag->flag_f = TRUE;
	else
		return (1);
	return (0);
}

void			ft_errorflag(t_flagl *flag, char **tab_flag, char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-Rlartgs1of] [file ...]\n");
	if (flag)
		free(flag);
	if (tab_flag)
		ft_freetab(tab_flag);
	exit(1);
}

t_flagl			*ft_getflagl(char **tab_flag)
{
	int			i;
	int			j;
	t_flagl		*flag;

	if (!(flag = ft_creatflag()))
		ft_mallocfail(NULL, NULL, tab_flag);
	i = 0;
	while (tab_flag[i])
	{
		j = 1;
		if (tab_flag[i][j] == '-' && tab_flag[i][j + 1] == '\0')
			break ;
		while (tab_flag[i][j])
		{
			if (ft_checkflag(tab_flag[i][j], flag))
				ft_errorflag(flag, tab_flag, tab_flag[i][j]);
			j++;
		}
		i++;
	}
	ft_freetab(tab_flag);
	return (flag);
}
