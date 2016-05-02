/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/02 20:26:26 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static int	ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (0);
}

static void	ft_editcmd(char *buf, char **cmdline)
{
	char	*kill;

	if (!*cmdline)
		*cmdline = ft_strdup(buf);
	else
	{
		kill = *cmdline;
		*cmdline = ft_strjoin(*cmdline, buf);
		free(kill);
	}
	ft_putstr(buf);
}

static void	ft_termcap(char *buf)
{
	char	*res;
	int		width;

	res = NULL;
	if (buf[2] == 67)
		res = tgetstr("nd", NULL);
	else if (buf[2] == 68)
		res = tgetstr("le", NULL);
	else
	{
		width = tgetnum("co");
		printf("%d\n", width);
	}
	if (res)
	{
		tputs(res, 0, &ft_putchar_int);
		dprintf(1, "\033[6n");
	}
}

void		ft_scanchr(char *buf, char **cmdline, t_conf *config)
{
	static int	success = 0;
	char		**split_env;

	if (buf[0] == '\t')
		return ;
	if (success == 0 && (split_env = ft_parseenv(config->env, "TERM"))
		&& *(split_env + 1))
		success = tgetent(NULL, *(split_env + 1));
	if (success == 1 && buf[0] == 033)
		ft_termcap(buf);
	if (buf[1] == '\0' || buf[2] == '\0')
		ft_editcmd(buf, cmdline);
}
