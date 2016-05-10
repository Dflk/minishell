/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saverestore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:30:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/05 16:46:59 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_erase(void)
{
	char *res;

	if ((res = tgetstr("dc", NULL)))
		tputs(res, 0, &ft_putchar_int);
}
