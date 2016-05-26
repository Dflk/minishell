/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saverestore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:30:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/26 18:38:15 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void		ft_erase(t_ctlinput *ctl)
{
	char	*res;
	int		posX;
	int		posY;

	res = tgetstr("dc", NULL);
	if (!res)
		return ;
	posX = ctl->posX;
	posY = ctl->posY;
	ft_savecursor();
	while (ctl->posX < ctl->len_cmd)
	{
		tputs(res, 0, &ft_putchar_int);
		ft_moveright(ctl);
	}
	ft_restorecursor();
	ctl->posX = posX;
	ctl->posY = posY;
}
