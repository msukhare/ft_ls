/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukhare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:40:30 by msukhare          #+#    #+#             */
/*   Updated: 2018/02/01 11:18:58 by msukhare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <grp.h>
# include <pwd.h>
# include "../libft/include/libft.h"
# include <time.h>
# define FALSE 0
# define TRUE 1

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct passwd	t_user;
typedef struct group	t_grp;
typedef struct			s_file
{
	char				*name;
	struct s_file		*next;
	char				*usr;
	char				*grp;
	char				*date;
	size_t				type;
	char				acl;
	t_stat				buf_stat;
}						t_file;
typedef struct			s_drfl
{
	char				*name;
	int					val;
	mode_t				st_mode;
	time_t				time;
	struct s_drfl		*next;
}						t_drfl;
typedef struct			s_flagl
{
	size_t				flag_recu;
	size_t				flag_l;
	size_t				flag_a;
	size_t				flag_r;
	size_t				flag_t;
	size_t				flag_g;
	size_t				flag_s;
	size_t				flag_uno;
	size_t				flag_f;
	size_t				flag_o;
}						t_flagl;
t_file					*ft_readdir(char *str);
void					ft_readlist(t_drfl *begin_list, int size,\
		t_flagl *flag);
int						ft_checkfile(t_drfl *begin_list);
void					ft_readdirs(char **tab_file);
t_file					*ft_readdirflag(t_flagl *flag, char *str);
void					ft_putlist_infol(t_file *begin_list, t_flagl *flag);
int						ft_managel(t_flagl *flag, t_file *bg_lst, char *str);
int						ft_printffiles(t_drfl *begin_list, t_flagl *flag,\
		int size);
int						ft_putinfoforfile(t_drfl *link, t_flagl *flag);
void					ft_free_lst_drfl(t_drfl *begin_list, t_flagl *flag);
void					ft_freeerrorlst_flag(t_drfl *begin_list, t_flagl *flag);
int						ft_freeerror(char *usr, char *grp, char *date);
void					ft_mallocfail(DIR *dir, t_file *begin_list, char **tab);
void					ft_freetab(char **tab_file);
t_file					*ft_helpformerge(int scmed, t_file *sp_l);
t_file					*ft_sort(t_file *bg_lst, int n, int order);
void					ft_getsizeblocks(t_file *begin_list, t_flagl *flag);
void					ft_putinfol(t_file *link, t_flagl *flag);
void					ft_getright(mode_t st_mode, char acl);
char					ft_getacl(char *path);
int						ft_lstlen(t_file *begin_list);
void					ft_sorttabfile(char **tab_file, int order);
void					ft_sortlistfile(t_file *begin_list, int order);
int						ft_userecu(t_flagl *flag, char *str);
void					ft_inlistdel(t_file *begin_list);
void					ft_initelemlist(t_file *begin_list);
t_drfl					*ft_splitlst(char **tab_file);
t_file					*ft_createlem(char *str, unsigned char type);
void					ft_dellist(t_file *begin_list);
void					ft_putlist(t_file *begin_list);
void					ft_getintab(int argc, char **argv, char ***tb_flg,\
		char ***tb_fl);
char					*ft_getlinks(char *name, char *path);
char					*ft_getdate(time_t date);
void					ft_dellastcar(char *str);
char					*ft_getname(t_stat buf, int usr_or_grp);
t_flagl					*ft_getflagl(char **tab_flag);
void					ft_errorflag(t_flagl *flag, char **tab_flag, char c);
void					ft_displayfilesflag(char **tab_flag, char **tab_files);
void					ft_stdrfl(t_drfl *begin_list, int order);
void					ft_helpswp(t_drfl *index, t_drfl *to_swp);
int						ft_checkinfo(t_drfl *begin_list);
char					*ft_creatpath(char *str, t_file *link, int type);
#endif
