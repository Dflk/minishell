/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 14:19:42 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/02 10:33:39 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static char	**ft_parseparam(char **cmd_split, unsigned char *params)
{
	int		i;

	while (cmd_split && *cmd_split && ft_strcmp(*cmd_split, "--")
			&& *cmd_split[0] == '-')
	{
		i = 0;
		while ((*cmd_split)[++i] != '\0')
		{
			if ((*cmd_split)[i] == 'i')
				*params |= PARAM_I;
			else if ((*cmd_split)[i] == 'v')
				*params |= PARAM_V;
		}
		cmd_split++;
	}
	return (cmd_split);
}

static void	ft_parsesetenv(char **cmd_split, t_conf *env_send)
{
	size_t	size_split;
	char	**new_env;

	size_split = ft_splitsize(env_send->env);
	if (size_split == 0)
		new_env = (char**)ft_memalloc(sizeof(char*) * 2);
	else
		new_env = ft_fillenv(env_send->env, size_split + 1);
	if (new_env)
	{
		if (size_split == 0)
		{
			new_env[0] = ft_strdup(*cmd_split);
			new_env[1] = NULL;
		}
		else
		{
			new_env[size_split + 1] = NULL;
			new_env[size_split] = ft_strdup(*cmd_split);
			ft_free_split(env_send->env);
			free(env_send->env);
		}
		env_send->env = new_env;
	}
}

void		ft_env(t_conf *config, char **cmd_split)
{
	unsigned char	params;
	t_conf			env_send;

	if (!*(cmd_split + 1))
	{
		ft_printenv(config->env);
		return ;
	}
	params = 0;
	cmd_split = ft_parseparam(cmd_split + 1, &params);
	if (params & PARAM_I)
		env_send.env = NULL;
	else
		env_send.env = ft_fillenv(config->env, ft_splitsize(config->env));
	while (cmd_split && *cmd_split && ft_strchr(*cmd_split, '='))
	{
		ft_parsesetenv(cmd_split, &env_send);
		cmd_split++;
	}
	ft_printenv(env_send.env);
}
