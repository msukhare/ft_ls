/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creatpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:20:18 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:48:17 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*ft_pushbackcara(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i >= 1 && str[i - 1] == '/')
		return (ft_strdup(str));
	return (ft_strjoin(str, "/"));
}

char		*ft_creatpath(char *str, t_file *link, int type)
{
	char	*tmp;
	char	*to_free;

	if (!(tmp = ft_pushbackcara(str)))
		return (NULL);
	to_free = tmp;
	if (!(tmp = ft_strjoin(tmp, link->name)))
	{
		free(to_free);
		return (NULL);
	}
	free(to_free);
	if (type == 1)
	{
		to_free = tmp;
		if (!(tmp = ft_pushbackcara(tmp)))
		{
			free(to_free);
			return (NULL);
		}
		free(to_free);
	}
	return (tmp);
}
