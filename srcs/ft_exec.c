/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 10:41:48 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 15:44:58 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

void		ft_execcmd(t_bin *cmd, char **cmdline_split, t_conf *config)
{
	char	*fullpath;
	pid_t	father;
	int		stat_loc;

	if ((father = fork()) == -1)
		return ;
	if (cmd)
		fullpath = ft_strjoin(cmd->path, cmd->name);
	else
		fullpath = *cmdline_split;
	if (father == 0)
	{
		execve(fullpath, cmdline_split, config->env);
		exit(1);
	}
	else
		waitpid(father, &stat_loc, 0);
	if (cmd)
		free(fullpath);
}
