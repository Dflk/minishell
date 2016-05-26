/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:06:19 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/26 21:17:27 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static void	ft_checkcmd(char *cmdline, t_conf *config)
{
	char		**cmdline_split;
	static void	(*tabf[5])(t_conf *, char **) = {&ft_cd, &ft_exit,
		&ft_unsetenv, &ft_env, &ft_setenv};
	int			builtin;
	t_bin		*cmd;

	cmd = NULL;
	if (!cmdline || !*cmdline || !(cmdline_split = ft_strsplit(cmdline, ' ')))
		return ;
	if ((builtin = ft_findbuiltin(*cmdline_split)) != -1)
		(tabf[builtin])(config, cmdline_split);
	else if (*cmdline_split[0] == '/' ||
			*cmdline_split[0] == '.' ||
			(cmd = ft_findcmd(*cmdline_split, ft_hashsearch(config,
															*cmdline_split))))
		ft_execcmd(cmd, cmdline_split, config);
	else
		ft_error(*cmdline_split, CMD_NOTFOUND, KEEP);
}

static void	ft_splitcmd(t_conf *config, char *cmdline)
{
	char	**split;
	char	**splitbuf;

	if ((split = ft_strsplit(cmdline, ';')))
	{
		splitbuf = split;
		while (split && *split)
		{
			ft_checkcmd(*split, config);
			split++;
		}
		ft_free_split(splitbuf);
		free(splitbuf);
	}
}

void		ft_minishell(t_conf *config)
{
	static char	*cmdline = NULL;

	ft_printprompt();
	signal(SIGINT, SIG_IGN);
	if (cmdline)
	{
		free(cmdline);
		cmdline = NULL;
	}
	while (1)
	{
		cmdline = ft_scaninput(config);
		ft_splitcmd(config, cmdline);
		ft_printprompt();
	}
}
