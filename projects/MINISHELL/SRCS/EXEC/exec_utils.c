/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:50 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:13:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	err_pipe(void)
{
	write(2, "pipe failed\n", 12);
	exit(127);
}

void	err_fork(void)
{
	write(2, "fork failed\n", 12);
	exit(127);
}

char	*find_path(char *cmd, t_data *data)
{
	int		i;
	char	*part_path;
	char	**paths;
	char	*path;

	i = 0;
	part_path = only_print_var("PATH", &data->env);
	if (!part_path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	paths = ft_split(part_path, ':');
	free(part_path);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
		{
			i = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), NULL);
}

void	exec_cmd(t_data *data, char **cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd[0])
		return ;
	path = find_path(cmd[0], data);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
		exit(127);
}
