/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 14:43:47 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/20 15:44:55 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int		ft_accessdir(char *path)
{
	struct stat	stats;

	if (access(path, F_OK) == -1)
	{
		ft_error(path, FILE_NOTFOUND, KEEP);
		return (0);
	}
	if (stat(path, &stats))
	{
		ft_error(path, "stat does not work :/, can't check type of file", KEEP);
		return (0);
	}
	else
		if (!(S_ISDIR(stats.st_mode)))
		{
			ft_error(path, FILE_NOTDIR, KEEP);
			return (0);
		}
	if (access(path, X_OK) == -1)
	{
		ft_error(path, FILE_PERMDENIED, KEEP);
		return (0);
	}
	return (1);
}
