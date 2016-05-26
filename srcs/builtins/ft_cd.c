/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 12:29:17 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/26 20:57:46 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_cd(t_conf *config, char **cmd_split)
{
	char	**parsenv;
	char	*path;

	parsenv = NULL;
	path = NULL;
	if (!(*(cmd_split + 1)) || !ft_strcmp(*(cmd_split + 1), "~"))
	{
		if ((parsenv = ft_parseenv(config->env, "HOME")))
			path = parsenv[1];
	}
	else
		path = *(cmd_split + 1);
	if (ft_access(path, DIRECTORY))
		chdir(path);
	if (parsenv)
	{
		ft_free_split(parsenv);
		free(parsenv);
	}
}
