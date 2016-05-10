/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movearrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/05 20:52:26 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_move(char *cmd, t_ctlinput *ctl)
{
	char	*res;
	int		i;

	res = tgetstr(cmd, NULL);
	if (res)
	{
		tputs(res, 0, &ft_putchar_int);
		if (ft_strcmp(cmd, "do") == 0)
		{
			res = tgetstr("le", NULL);
			ctl->posY++;
			i = ctl->termsize->ws_col + 1;
			while (--i >= 0)
				tputs(res, 0, &ft_putchar_int);
		}
		else
		{
			res = tgetstr("nd", NULL);
			ctl->posY--;
			i = -1;
			while (++i <= ctl->termsize->ws_col)
				tputs(res, 0, &ft_putchar_int);
		}
	}
}

void	ft_movearrow(char *buf, t_ctlinput *ctl)
{
	char	*res;
	int		way;

	res = NULL;
	way = ft_strcmp(buf, "nd");
	if (!way)
	{
		if (ctl->posX / ctl->termsize->ws_col == ctl->posY)
			res = tgetstr("nd", NULL);
		else
			ft_move("do", ctl);
	}
	else
	{
		if (ctl->posX / ctl->termsize->ws_col == ctl->posY)
			res = tgetstr("le", NULL);
		else
			ft_move("up", ctl);
	}
	if (res)
		tputs(res, 0, &ft_putchar_int);
}
