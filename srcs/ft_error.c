/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 12:55:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/15 13:48:40 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_error(char *name, char *error, int flag_exit)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	if (name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putchar_fd('\n', 2);
	if (flag_exit == EXIT)
		exit(1);
}
