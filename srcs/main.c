/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 09:11:54 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 15:33:42 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

int		main(int argc, char **argv, char **env)
{
	t_conf	*config;
	int		i;

	config = NULL;
	i = 0;
	if (argc != 1 || !argv)
		return (0);
	if (env)
		config = ft_fillconf(env);
	if (config)
	{
		ft_hashtable(config);
		ft_minishell(config);
	}
	return (0);
}
