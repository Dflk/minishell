/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:55:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/22 10:32:19 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <libft.h>
# include "minishell_typedefs.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>

/*
** Flag error_exit
*/
# define EXIT 0
# define KEEP 1

/*
** Error Type
*/
# define CMD_NOTFOUND		"command not found"
# define FILE_NOTFOUND		"no such file or directory"
# define FILE_NOTDIR		"not a directory"
# define FILE_PERMDENIED	"permission denied"
# define FEW_ARG			"Too few arguments"
# define MANY_ARG			"Too many arguments"

/*
** Binary mask (param cmd env)
*/
# define PARAM_V 0000000
# define PARAM_I 0000001

/*
** Error function
*/
void	ft_error(char *name, char *error, int flag_exit);

/*
** Manage lst
*/
t_bin	*ft_findlast(t_bin *bin);

/*
** Creating config (environment + bin)
*/
t_conf	*ft_fillconf(char **env);

/*
** Manage environment
*/
char	**ft_parseenv(char **env, char *variable);
int		ft_findenv(char **env, char *variable);
char	**ft_fillenv(char **env, size_t size);
void	ft_printenv(char **env);

/*
** Free
*/
void	ft_free_split(char **split);
void	ft_free_bin(t_bin **bin);

/*
** Shell prompt
*/
void	ft_printprompt(void);

/*
** Builtins
*/
void	ft_cd(t_conf *config, char **cmd_split);
void	ft_exit(t_conf *config, char **cmd_split);
void	ft_unsetenv(t_conf *config, char **cmd_split);
void	ft_setenv(t_conf *config, char **cmd_split);
void	ft_env(t_conf *config, char **cmd_split);

/*
** Access dir/file
*/
int		ft_accessdir(char *path);

/*
** Exec commands
*/
void	ft_minishell(t_conf *config);
t_bin	*ft_findcmd(char *cmd, t_bin *cmds);
void	ft_execcmd(t_bin *cmd, char **cmdline_split, t_conf *config);
int		ft_findbuiltin(char *cmd);

/*
** Utils
*/
size_t	ft_splitsize(char **split);

#endif
