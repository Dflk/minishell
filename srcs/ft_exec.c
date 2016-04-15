/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 10:41:48 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/14 13:50:32 by rbaran           ###   ########.fr       */
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
	fullpath = ft_strjoin(cmd->path, cmd->name);
	if (father == 0)
	{
		execve(fullpath, cmdline_split, config->env);
		exit(1);
	}
	else
		waitpid(father, &stat_loc, 0);
	free(fullpath);
}
