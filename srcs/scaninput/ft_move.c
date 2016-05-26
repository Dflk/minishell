/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/26 17:03:38 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_moveup(t_ctlinput *ctl)
{
	char	*res;
	int		i;

	res = tgetstr("up", NULL);
	if (!res)
		return ;
	tputs(res, 0, &ft_putchar_int);
	res = tgetstr("nd", NULL);
	ctl->posY--;
	i = -1;
	while (++i <= ctl->termsize->ws_col)
		tputs(res, 0, &ft_putchar_int);
}

static void	ft_movedown(t_ctlinput *ctl)
{
	char	*res;
	int		i;

	res = tgetstr("do", NULL);
	if (!res)
		return ;
	tputs(res, 0, &ft_putchar_int);
	res = tgetstr("le", NULL);
	ctl->posY++;
	i = ctl->termsize->ws_col;
	while (--i >= 0)
		tputs(res, 0, &ft_putchar_int);
}

void		ft_moveright(t_ctlinput *ctl)
{
	char	*res;

	res = NULL;
	if (ctl->posX >= ctl->len_cmd)
		return ;
	ctl->posX++;
	if (ctl->posX / ctl->termsize->ws_col == ctl->posY)
		res = tgetstr("nd", NULL);
	else
		ft_movedown(ctl);
	if (res)
		tputs(res, 0, &ft_putchar_int);
}

void		ft_moveleft(t_ctlinput *ctl)
{
	char	*res;

	res = NULL;
	if (ctl->posX == ctl->initposX)
		return ;
	ctl->posX--;
	if (ctl->posX / ctl->termsize->ws_col == ctl->posY)
		res = tgetstr("le", NULL);
	else
		ft_moveup(ctl);
	if (res)
		tputs(res, 0, &ft_putchar_int);
}
