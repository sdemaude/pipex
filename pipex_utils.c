/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:51:44 by sdemaude          #+#    #+#             */
/*   Updated: 2024/02/18 12:41:51 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char static	*find_path(char **envp, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (envp)
	{
		j = 0;
		while ((*envp)[j] == to_find[j])
		{
			j++;
			if (!to_find[j])
				return (*envp + 5);
		}
		envp++;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_valid_path(char *cmd, char **envp)
{
	int		i;
	char	**array;
	char	*path_line;
	char	*path;
	char	*tmp;

	i = -1;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_line = find_path(envp, "PATH=");
	array = ft_split(path_line, ':');
	while (array[++i])
	{
		tmp = ft_strjoin(array[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free_tab(array);
			return (path);
		}
		free(path);
	}
	free_tab(array);
	return (NULL);
}
