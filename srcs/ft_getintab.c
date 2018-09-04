/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getintab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:45:21 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:49:05 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*ft_gtstr(char *str, int *bol)
{
	if (*bol == 1)
		*bol = 0;
	return (ft_strdup(str));
}

static void	ft_getsize(char **argv, int *size_flag, int *size_file)
{
	int		i;
	int		bol;

	i = 1;
	*size_flag = 0;
	*size_file = 0;
	bol = 1;
	while (argv[i] && argv[i][0] != '\0')
	{
		if (bol && argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '\0')
			ft_errorflag(NULL, NULL, '-');
		if (bol && argv[i][0] == '-' && argv[i][1] != '\0' &&
			((argv[i][1] == '-' && argv[i][2] == '\0') || argv[i][1] != '-'))
			(*size_flag)++;
		else
		{
			(bol) ? bol = 0 : 0;
			(*size_file)++;
		}
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
			bol = 0;
		i++;
	}
}

static int	ft_putintabavflag(char **tb_fg, char **tb_fl, char **ag)
{
	int		i;
	int		in_flag;
	int		in_file;
	int		bol;

	i = 1;
	in_flag = 0;
	in_file = 0;
	bol = 1;
	while (ag[i] && ag[i][0] != '\0')
	{
		if (bol && tb_fg && ag[i][0] == '-' && ag[i][1] != '\0' &&
			((ag[i][1] == '-' && ag[i][2] == '\0') || ag[i][1] != '-'))
			(!(tb_fg[in_flag++] = ft_strdup(ag[i]))) ? exit(1) : 0;
		else
			(!(tb_fl[in_file++] = ft_gtstr(ag[i], &bol))) ? exit(1) : 0;
		(ag[i][0] == '-' && ag[i][1] == '-' && ag[i][2] == '\0') ? bol = 0 : 0;
		i++;
	}
	(tb_fl) ? tb_fl[in_file] = 0 : 0;
	(tb_fg) ? tb_fg[in_flag] = 0 : 0;
	return (i);
}

void		ft_getintab(int argc, char **argv, char ***tb_flg, char ***tb_fl)
{
	int		size_flag;
	int		size_file;

	ft_getsize(argv, &size_flag, &size_file);
	if (size_flag != 0)
	{
		if (!(*tb_flg = (char**)malloc(sizeof(char*) * (size_flag + 1))))
			exit(1);
	}
	if (size_file != 0)
	{
		if (!(*tb_fl = (char**)malloc(sizeof(char*) * (size_file + 1))))
			exit(1);
	}
	if (ft_putintabavflag(*tb_flg, *tb_fl, argv) < argc)
	{
		ft_putstr_fd("ft_ls : fts_open: No such file or directory\n", 2);
		(*tb_flg) ? ft_freetab(*tb_flg) : 0;
		(*tb_fl) ? ft_freetab(*tb_fl) : 0;
		exit(1);
	}
}
