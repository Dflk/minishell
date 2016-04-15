/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:55:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/15 15:45:36 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL
# define FT_MINISHELL
# include <libft.h>
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
# define CMD_NOTFOUND "command not found"
# define FILE_NOTFOUND "no such file or directory"
# define FILE_NOTDIR "not a directory"
# define FILE_PERMDENIED "permission denied"

typedef struct dirent	t_dirent;

typedef struct	s_bin
{
	char			*name;
	char			*path;
	struct s_bin	*next;
}				t_bin;

typedef struct	s_conf
{
	t_bin	*bin;
	char	**env;
}				t_conf;

/*
** Error function
*/
void	ft_error(char *name, char *error, int flag_exit);

/*
** Manage lst
*/
t_bin	*ft_findlast(t_bin *bin);

/*
** Creating env
*/
t_conf	*ft_fillconf(char **env);

/*
** Parsing environment by variable
*/
char	**ft_parseenv(char **env, char *variable);

/*
** Free
*/
void	ft_free_split(char **split);

/*
** Shell prompt
*/
void	ft_printprompt(void);

/*
** Builtins
*/
void	ft_cd(t_conf *config, char **cmd_split);

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

#endif
