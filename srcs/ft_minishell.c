/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:06:19 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/15 13:51:49 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static void	ft_checkcmd(char *cmdline, t_conf *config)
{
	char		**cmdline_split;
	static void	(*tabf[1])(t_conf *, char **) = { &ft_cd };
	int			builtin;
	t_bin		*cmd;

	if (!cmdline || !(cmdline_split = ft_strsplit(cmdline, ' ')))
		return ;
	if ((builtin = ft_findbuiltin(*cmdline_split)) != -1)
		(tabf[builtin])(config, cmdline_split);
	else if ((cmd = ft_findcmd(*cmdline_split, config->bin)))
		ft_execcmd(cmd, cmdline_split, config);
	else
		ft_error(*cmdline_split, CMD_NOTFOUND, KEEP);
}

void		ft_minishell(t_conf *config)
{
	char	*cmdline;

	ft_printprompt();
	while (get_next_line(0, &cmdline))
	{
		ft_checkcmd(cmdline, config);
		ft_printprompt();
		free(cmdline);
	}
}
