/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 10:45:53 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 08:49:13 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_putlist(t_file *begin_list)
{
	t_file	*tmp;

	tmp = begin_list;
	if (!begin_list)
		return ;
	while (tmp)
	{
		if (tmp->name[0] != '.')
			ft_putendl(tmp->name);
		tmp = tmp->next;
	}
	ft_dellist(begin_list);
}

void		ft_dellist(t_file *begin_list)
{
	t_file	*tmp;

	while (begin_list)
	{
		tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->name);
		free(tmp);
	}
}

t_file		*ft_createlem(char *str, unsigned char type)
{
	t_file	*new_elem;

	if (!(new_elem = (t_file*)malloc(sizeof(t_file) * 1)))
		return (NULL);
	if (!(new_elem->name = ft_strdup(str)))
	{
		free(new_elem);
		return (NULL);
	}
	new_elem->type = (size_t)type;
	new_elem->next = NULL;
	return (new_elem);
}

t_drfl		*ft_splitlst(char **tab_file)
{
	int		i;
	t_drfl	*begin_list;
	t_drfl	*tmp;

	i = 0;
	if (!(begin_list = (t_drfl*)malloc(sizeof(t_drfl))))
		ft_mallocfail(NULL, NULL, tab_file);
	if (!(begin_list->name = ft_strdup(tab_file[i++])))
		ft_mallocfail(NULL, NULL, tab_file);
	tmp = begin_list;
	tmp->val = 0;
	while (tab_file[i])
	{
		if (!(tmp->next = (t_drfl*)malloc(sizeof(t_drfl))))
			ft_mallocfail(NULL, NULL, tab_file);
		tmp = tmp->next;
		if (!(tmp->name = ft_strdup(tab_file[i])))
			ft_mallocfail(NULL, NULL, tab_file);
		tmp->val = 0;
		i++;
	}
	tmp->next = NULL;
	ft_freetab(tab_file);
	return (begin_list);
}
