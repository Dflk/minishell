/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillconf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 10:25:02 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/02 10:52:19 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static t_bin	*ft_addbin(char *name, char *path)
{
	t_bin	*bin;

	if ((bin = (t_bin*)ft_memalloc(sizeof(t_bin))))
	{
		bin->name = ft_strdup(name);
		if (path[ft_strlen(path)] != '/')
			bin->path = ft_strjoin(path, "/");
		else
			bin->path = ft_strdup(path);
		bin->next = NULL;
	}
	return (bin);
}

static t_bin	*ft_fillconfbins(DIR *directory, char *path)
{
	t_dirent		*readfile;
	t_bin			*bin_buf_begin;
	t_bin			*bin_buf;

	bin_buf_begin = NULL;
	while ((readfile = readdir(directory)) != NULL)
		if (ft_strcmp(readfile->d_name, ".") &&
				ft_strcmp(readfile->d_name, ".."))
		{
			if (!bin_buf_begin)
			{
				bin_buf_begin = ft_addbin((char*)readfile->d_name, path);
				bin_buf = bin_buf_begin;
			}
			else
			{
				bin_buf->next = ft_addbin((char*)readfile->d_name, path);
				bin_buf = bin_buf->next;
			}
		}
	return (bin_buf_begin);
}

static t_bin	*ft_readconfpaths(char **paths_bin)
{
	DIR			*directory;
	struct stat	stats;
	t_bin		*bin;
	t_bin		*bin_last;

	bin = NULL;
	while (paths_bin && *paths_bin)
	{
		if (!(stat(*paths_bin, &stats)))
			if ((directory = opendir(*paths_bin)))
			{
				if (!bin)
				{
					bin = ft_fillconfbins(directory, *paths_bin);
					bin_last = ft_findlast(bin);
				}
				else
				{
					bin_last->next = ft_fillconfbins(directory, *paths_bin);
					bin_last = ft_findlast(bin);
				}
				closedir(directory);
			}
		paths_bin++;
	}
	return (bin);
}

t_conf			*ft_fillconf(char **env)
{
	char	**split_bins;
	char	**split_path_bins;
	t_conf	*config;

	if (!(config = ft_memalloc(sizeof(t_conf))))
		return (NULL);
	config->env = ft_fillenv(env, ft_splitsize(env));
	split_bins = NULL;
	split_path_bins = NULL;
	if ((split_bins = ft_parseenv(config->env, "PATH")))
	{
		if ((split_path_bins = ft_strsplit(split_bins[1], ':')))
		{
			config->bin = ft_readconfpaths(split_path_bins);
			ft_free_split(split_path_bins);
			free(split_path_bins);
		}
		ft_free_split(split_bins);
		free(split_bins);
	}
	return (config);
}
