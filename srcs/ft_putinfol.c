/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putinfol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:06:36 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:50:22 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		ft_gettype(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('f');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else
		return ('-');
}

char			ft_getacl(char *path)
{
	char		to_ret;
	acl_t		acl;
	acl_entry_t	tmp;
	ssize_t		help;

	acl = NULL;
	to_ret = ' ';
	help = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && (acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp)) == -1)
	{
		acl_free(acl);
		acl = NULL;
		return (to_ret);
	}
	if (help < 0)
		help = 0;
	if (help > 0)
		to_ret = '@';
	else if (acl != NULL)
		to_ret = '+';
	acl_free(acl);
	return (to_ret);
}

void			ft_getright(mode_t st_mode, char acl)
{
	char		right[12];

	right[0] = ft_gettype(st_mode);
	right[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	right[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	right[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	right[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	right[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	right[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	right[7] = (st_mode & S_IROTH) ? 'r' : '-';
	right[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	right[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	if ((st_mode & S_ISVTX))
		right[9] = (right[9] == '-') ? 'T' : 't';
	if ((st_mode & S_ISUID))
		right[3] = (right[3] == '-' ? 'S' : 's');
	if ((st_mode & S_ISGID))
		right[6] = (right[6] == '-' ? 'S' : 's');
	right[10] = acl;
	right[11] = '\0';
	ft_printf("%s\t", right);
}

void			ft_putinfol(t_file *link, t_flagl *flag)
{
	ft_getright(link->buf_stat.st_mode, link->acl);
	ft_printf("%hu\t", link->buf_stat.st_nlink);
	if (flag->flag_g == FALSE)
		ft_printf("%s\t", link->usr);
	if (flag->flag_o == FALSE)
		ft_printf("%s\t", link->grp);
	if (major(link->buf_stat.st_rdev) != 0)
		ft_printf("%d, %d\t", major(link->buf_stat.st_rdev),\
				minor(link->buf_stat.st_rdev));
	else
		ft_printf("%llu\t", link->buf_stat.st_size);
	ft_printf("%s\t", link->date);
}

void			ft_getsizeblocks(t_file *begin_list, t_flagl *flag)
{
	long long	total;
	int			i;

	total = 0;
	i = 0;
	while (begin_list)
	{
		while (flag->flag_a == FALSE && begin_list &&
				begin_list->name[0] == '.')
			begin_list = begin_list->next;
		if (begin_list)
		{
			i++;
			total += begin_list->buf_stat.st_blocks;
			begin_list = begin_list->next;
		}
	}
	if (i != 0)
		ft_printf("total %llu\n", total);
}
