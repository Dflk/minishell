/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 16:51:49 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static void	ft_editrmcmd(char **cmdline, t_ctlinput *ctl)
{
	if (!*cmdline || ctl->posX == ctl->initposX)
		return ;
	ctl->posX--;
	ft_movearrow("le", ctl);
	ctl->len_cmd--;
	ft_memmove((*cmdline) + (ctl->posX - ctl->initposX),
				((*cmdline) + (ctl->posX - ctl->initposX + 1)),
				ft_strlen((*cmdline) + (ctl->posX - ctl->initposX + 1)) + 1);
	ft_savecursor();
	ft_putstr((*cmdline) + (ctl->posX - ctl->initposX));
	ft_erase();
	ft_restorecursor();
}

static void	ft_editcmd(char *buf, char **cmdline, t_ctlinput *ctl)
{
	char	*kill;

	ctl->len_cmd++;
	if (!*cmdline)
		*cmdline = ft_strdup(buf);
	else
	{
		kill = *cmdline;
		if ((*cmdline = ft_strnew(ctl->len_cmd + 1)))
		{
			ft_strncpy(*cmdline, kill, ctl->posX - ctl->initposX);
			ft_strcat(*cmdline, buf);
			ft_strcat(*cmdline, kill + ctl->posX - ctl->initposX);
			free(kill);
		}
	}
	ft_savecursor();
	ft_putstr((*cmdline) + (ctl->posX - ctl->initposX));
	ctl->posX++;
	if (ctl->posX + 1 != ctl->len_cmd)
	{
		ft_restorecursor();
		ft_movearrow("nd", ctl);
	}
	if (ctl->posX / ctl->termsize->ws_col != ctl->posY)
		ctl->posY++;
}

void		ft_scanchr(char *buf, char **cmdline, t_conf *config,
				t_ctlinput *ctl)
{
	if (buf[0] == '\t')
		return ;
	if (config->term == 1 && buf[0] == 127)
		ft_editrmcmd(cmdline, ctl);
	else if (config->term == 1 && buf[0] == 033 && buf[2] == 67
			&& ctl->posX < ctl->len_cmd)
	{
		ctl->posX++;
		ft_movearrow("nd", ctl);
	}
	else if (config->term == 1 && buf[0] == 033 && buf[2] == 68
			&& ctl->posX > ctl->initposX)
	{
		ctl->posX--;
		ft_movearrow("le", ctl);
	}
	else if (ft_isprint(buf[0]))
		ft_editcmd(buf, cmdline, ctl);
}
