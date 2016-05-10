/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scaninput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 12:01:46 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/04 19:19:49 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static int	ft_checkfirstpos(void)
{
	char	buf[256];
	char	*buffer;

	if (getcwd(buf, 256))
	{
		if ((buffer = ft_strrchr((char *)buf, '/')) && *(buffer + 1))
			return ((int)ft_strlen(buffer + 1) + 3);
		else
			return ((int)ft_strlen((char *)buf + 3));
	}
	return (0);
}

static void	ft_scan(char **cmdline, t_conf *config, t_ctlinput ctl)
{
	char		buf[5];
	int			ret;

	ctl.initposX = ft_checkfirstpos();
	ctl.posX = ctl.initposX;
	ctl.len_cmd = ctl.posX;
	ctl.posY = 0;
	while ((ret = read(0, buf, 4)) != -1)
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
			return ;
		ft_scanchr((char*)buf, cmdline, config, &ctl);
	}
}

static void	ft_termios(void)
{
	static int				mode = 0;
	static struct termios	term_backup;
	struct termios			term;

	if (mode == 0)
	{
		if (tcgetattr(0, &term_backup)
			|| !ft_memcpy(&term, &term_backup, sizeof(struct termios)))
			ft_error(NULL, BACKUP_TERM, EXIT);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VTIME] = 0;
		term.c_cc[VMIN] = 1;
		if (tcsetattr(0, TCSADRAIN, &term))
			ft_error(NULL, SET_TERM, EXIT);
		mode = 1;
	}
	else
	{
		mode = 0;
		if (tcsetattr(0, TCSANOW, &term_backup))
			ft_error(NULL, SET_TERM, EXIT);
	}
}

char		*ft_scaninput(t_conf *config)
{
	char			*cmdline;
	t_ctlinput		ctl;

	cmdline = NULL;
	ft_termios();
	if ((ctl.termsize = (struct winsize*)ft_memalloc(sizeof(struct winsize))))
		ioctl(0, TIOCGWINSZ, ctl.termsize);
	ft_scan(&cmdline, config, ctl);
	ft_termios();
	ft_putchar('\n');
	return (cmdline);
}
