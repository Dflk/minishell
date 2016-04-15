/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 10:57:15 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/13 11:11:47 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_parseenv(char **env, char *name)
{
	char	**split;
	while (*env)
	{
		if ((split = ft_strsplit(*env, '=')))
		{
			if (*split && ft_strcmp(split[0], name) == 0)
				return (split);
			ft_free_split(split);
			free(split);
		}
		env++;
	}
	return (NULL);
}
