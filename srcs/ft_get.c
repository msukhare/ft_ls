/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:22:04 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:48:54 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*ft_getname(t_stat buf, int usr_or_grp)
{
	t_user	*usr;
	t_grp	*grp;

	if (usr_or_grp == 1)
	{
		if (!(usr = getpwuid(buf.st_uid)))
			return (ft_itoa(buf.st_uid));
		return (ft_strdup(usr->pw_name));
	}
	if (!(grp = getgrgid(buf.st_gid)))
		return (ft_itoa(buf.st_gid));
	return (ft_strdup(grp->gr_name));
}

void		ft_dellastcar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i > 1)
		str[i - 1] = '\0';
}

char		*ft_getdate(time_t date)
{
	char	*to_ret;
	char	*to_free;
	char	*tmp;
	time_t	now;

	now = time(NULL);
	if (date >= (now + 1) || date < (now - 15721200))
	{
		if (!(to_free = ft_strsub(ctime(&date), 20, 23)))
			return (NULL);
		if (!(to_ret = ft_strjoin(" ", to_free)))
			return (NULL);
		free(to_free);
		to_free = to_ret;
		tmp = ft_strsub(ctime(&date), 4, 6);
		to_ret = ft_strjoin(tmp, to_ret);
		(tmp) ? free(tmp) : 0;
		(to_free) ? free(to_free) : 0;
		(to_ret) ? ft_dellastcar(to_ret) : 0;
	}
	else
		to_ret = ft_strsub(ctime(&date), 4, 12);
	return (to_ret);
}

char		*ft_getlinks(char *name, char *path)
{
	char	*to_free;
	char	*to_ret;
	char	*buff;

	if (!(buff = (char*)ft_memalloc(256)))
		return (NULL);
	if ((readlink(path, buff, 256)) == -1)
	{
		free(buff);
		return (NULL);
	}
	if (!(to_ret = ft_strjoin(name, " -> ")))
		return (NULL);
	to_free = to_ret;
	to_ret = ft_strjoin(to_ret, buff);
	free(to_free);
	free(buff);
	free(name);
	return (to_ret);
}
