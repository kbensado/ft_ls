/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 11:15:15 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:44:41 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <time.h>
# include <dirent.h>
# include "libft/libft.h"
# include "ft_printf/includes/ft_printf.h"
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <uuid/uuid.h>

# define NB_FILE flag->nb_file
# define MAX_NAME flag->mlen_file_name
# define MAX_LEN_GROUP flag->mlen_file_group
# define MAX_LEN_OWN flag->mlen_file_own
# define MAX_NAME flag->mlen_file_name
# define MAX_SIZE flag->mlen_file_size
# define MAX_SIZE_MAJOR flag->mlen_file_major
# define MAX_SIZE_MINOR flag->mlen_file_minor
# define MAX_SIZE_LINK flag->mlen_file_link
# define BLOCK_SIZE_LEN flag->block_size_nbr
# define BLOCK_SIZE_FILE flag->block_size_file
# define BLOCK_SIZE_FILE_I flag->block_size_file_i
# define MAX_NAME_P flag->mlen_file_name_p
# define MAX_SIZE_P flag->mlen_file_size_p
# define MAX_LEN_GROUP_P flag->mlen_file_group_p
# define MAX_LEN_OWN_P flag->mlen_file_own_p
# define MAX_SIZE_MAJOR_P flag->mlen_file_major_p
# define MAX_SIZE_MINOR_P flag->mlen_file_minor_p
# define MAX_SIZE_LINK_P flag->mlen_file_link_p
# define BLOCK_SIZE_LEN_P flag->block_size_nbr_p
# define BLOCK_SIZE_FILE_P flag->block_size_file_p

# define BUFF_SIZE 4096
# define ERROR_USAGE "ls: illegal option -- -\nusage: ls [-FRSarst] [file ...]"

# define LSTAT_T1 lstat(set_path(root, buffer, path, 1), &stat) == 0
# define LSTAT_1 LSTAT_T1&&lstat(set_path(root,buffer,list->path,1),&stat2)==0
# define TIME_FIRST stat.st_mtimespec.tv_sec, stat.st_mtimespec.tv_nsec
# define TIME_SECOND stat2.st_mtimespec.tv_sec, stat2.st_mtimespec.tv_nsec
# define LSTAT_TIME time_cmp(TIME_FIRST, TIME_SECOND)
# define TIME_FIRST_1 stat.st_mtimespec.tv_sec, stat.st_mtimespec.tv_nsec
# define TIME_SECOND_1 stat2.st_mtimespec.tv_sec, stat2.st_mtimespec.tv_nsec
# define L_STAT_TIME2 !(time_cmp(TIME_FIRST_1, TIME_SECOND_1))
# define T_DIR_ARG &n_dir, buffer, NULL, get_pos_dir_r(n_dir, buffer, 0)
# define T_DIR_PUSH ft_list_push_dir(T_DIR_ARG)
# define T_DIR_ARG_2 &n_dir, buffer, NULL, get_pos_dir(n_dir, buffer, 0)
# define T_DIR_PUSH_2 ft_list_push_dir(T_DIR_ARG_2)
# define LIST_FILE_P ft_list_push(&tree, name, NULL, get_pos_r(tree, name, 0))
# define LIST_FILE_P_2 ft_list_push(&tree, name, NULL, get_pos(tree, name, 0))
# define LS_FILE_ARG &tree, name, NULL, get_pos_size_r(tree, name, 0, path)
# define LS_FILE_ARG_1 &tree, name, NULL, get_pos_size(tree, name, 0, path)
# define LS_FILE_ARG_2 &tree, name, NULL, get_pos_time_r(tree, name, 0, path)
# define LS_FILE_ARG_3 &tree, name, NULL, get_pos_time(tree, name, 0, path)
# define LIST_FILE_S ft_list_push(LS_FILE_ARG)
# define LIST_FILE_S_2 ft_list_push(LS_FILE_ARG_1)
# define LIST_FILE_T ft_list_push(LS_FILE_ARG_2)
# define LIST_FILE_T_2 ft_list_push(LS_FILE_ARG_3)
# define SYMLINK print_with_filter(path[cmp[0]], flag, "", 0)
# define SYMLINK_2 print_dir(path[cmp[0]], flag, key)

typedef struct stat		t_stat;
typedef struct dirent	t_dir;
typedef struct passwd	t_pass;
typedef struct group	t_group;

typedef struct			s_flag
{
	int					l;
	int					a;
	int					b_f;
	int					l_r;
	int					b_r;
	int					l_s;
	int					b_s;
	int					t;
	char				pwd[BUFF_SIZE];
	int					nb_file;
	int					mlen_file_name;
	int					mlen_file_size;
	int					mlen_file_link;
	int					mlen_file_own;
	int					mlen_file_group;
	int					mlen_file_major;
	int					mlen_file_minor;
	int					block_size_nbr;
	long long			block_size_file;
	int					block_size_file_i;
	int					mlen_file_name_p;
	int					mlen_file_own_p;
	int					mlen_file_group_p;
	int					mlen_file_size_p;
	int					mlen_file_link_p;
	int					mlen_file_major_p;
	int					mlen_file_minor_p;
	int					block_size_nbr_p;
	int					block_size_file_p;
}						t_flag;

typedef	struct			s_tree
{
	char				*path;
	long				size;
	long				time;
	struct s_tree		*next;
}						t_tree;

typedef struct			s_dir
{
	char				*path;
	long				size;
	long				time;
	struct s_dir		*next;
}						t_ndir;

/*
**			main.c
*/

int						main(int ac, char **av, char **env);

/*
**			dir.c
*/

void					print_dir(char *path, t_flag *flag, int key);

/*
**			error.c
*/

int						ft_error(char *str, int flag);
void					open_fail(char *path, t_flag *flag);

/*
**			file.c
*/

void					print_file(char *path, t_flag *flag, int key);

/*
**			flag.c
*/

int						get_flag(t_flag *list, char **arg, int i, char **env);

/*
**			launch.c
*/

void					set_file(char **path, int *cmp,
						t_flag *flag, int current);

/*
**			list.c
*/

int						get_pos(t_tree *list, char *path, int i);
t_tree					*ft_create_elem(char *path);
void					ft_list_clear(t_tree **begin_list);
void					ft_list_push(t_tree **begin_list, char *name,
						t_tree *tmp, int i);

/*
**			list2.c
*/

int						get_pos_r(t_tree *list, char *path, int i);
int						get_pos_time(t_tree *list, char *path,
						int i, char *root);
int						get_pos_size(t_tree *list, char *path,
						int i, char *root);
int						get_pos_time_r(t_tree *list, char *path,
						int i, char *root);
int						get_pos_size_r(t_tree *list, char *path,
						int i, char *root);

/*
**			list3.c
*/

int						get_pos_dir(t_ndir *list, char *path, int i);
void					ft_list_del_node(t_ndir **begin_list, char*path);
void					ft_list_push_dir(t_ndir **begin_list,
						char *name, t_ndir *tmp, int i);

/*
**			macro.c
*/

void					get_stat_of_file(char *path, t_flag *flag,
						char *buffer, DIR *dir);
int						path_is_dir(char *path, int i);
int						path_is_fifo(char *path);
char					**set_buffer(char *path, size_t i, int j, int len);
int						number_of_dir(DIR *fd, t_flag *flag);

/*
**			macro2.c
*/

void					sort_ascii(char **tab, t_flag *flag);
void					sort_ascii_rev(char **tab, t_flag *flag);
int						path_is_syml(char *path);
int						path_is_block(char *path);
int						path_is_socket(char *path);

/*
**			macro3.c
*/

void					clean_stat(t_flag *flag);
int						path_is_file(char *path);
long					get_time(char *path);
void					print_own(t_stat *stat, t_flag *flag, char *path);
int						ft_strcmpl(const char *s1, const char *s2);

/*
**			macro4.c
*/

void					set_stat(t_dir *dir, t_stat *status, t_flag *flag);
void					print_time(t_stat *status);
int						time_cmp(unsigned long t11, unsigned long t12,
						unsigned long t21, unsigned long t22);
void					print_group(t_stat *stat, t_flag *flag);
char					*set_path(char *path, char *buffer,
						char *name, int flag);

/*
**			macro5.c
*/

void					set_blank(t_flag *flag, t_stat *status, char *path);
void					get_name(char *path, int i, t_flag *flag, char *name);
int						list_size(t_tree *tree);
void					print_block(char *name, t_flag *flag, char *path);
void					get_block_dir(t_tree *tree, char *path);

/*
**			macro6.c
*/

void					write_f(char *path, char *name);
int						get_len_own(t_stat *stat);
int						get_len_group(t_stat *stat);
void					print_mn(t_stat *status, t_flag *flag);
void					print_privilege_ext(struct stat *l_stat, char *path);

/*
**			macro7.c
*/

int						has_acl(char *path, t_stat *l_stat);
int						*set_cmp(int i, int ac);
int						get_pos_dir_r(t_ndir *list, char *path, int i);
void					print_stat_n(t_flag *flag, t_stat *status);
void					print_dir_name(char *path, int len, int i);

/*
**			print.c
*/

void					print_link(char *path);
void					print_privilege(struct stat *l_stat, char *path);
void					print_stat(char *path, t_flag *list, char *name);
void					print_with_filter(char *path, t_flag *flag,
						char *name, int key);

#endif
