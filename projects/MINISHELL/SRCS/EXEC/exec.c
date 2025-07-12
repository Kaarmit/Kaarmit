/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:54 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:13:59 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	process(t_data *data, pid_t pid1)
{
	int	status;

	if (pid1 == 0)
	{
		if (is_dot(data->chunk->cmd))
			return (free_data_exec(data));
		if (is_dir(data->chunk->cmd))
			return (free_data_exec(data));
		redir(data->chunk);
		exec_cmd(data, data->chunk->args, data->envcpy);
	}
	waitpid(pid1, &status, 0);
	single_exit_s(WEXITSTATUS(status), UPDATE);
	// close(data->stdin);
	// close(data->stdout);
	return ;
}

void	exec(t_data *data)
{
	pid_t	pid111;

	if (!data->chunk->args)
	{
		data->stdin = dup(0);
		data->stdout = dup(1);
		redir(data->chunk);
		dup2(data->stdin, STDIN_FILENO);
		dup2(data->stdout, STDOUT_FILENO);
		close(data->stdin);
		close(data->stdout);
		return ;
	}
	else if (is_builtin(data->chunk->cmd))
	{
		data->stdin = dup(0);
		data->stdout = dup(1);
		redir(data->chunk);
		do_builtin(data, data->chunk, data->chunk->cmd);
		dup2(data->stdin, STDIN_FILENO);
		dup2(data->stdout, STDOUT_FILENO);
		close(data->stdin);
		close(data->stdout);
		return ;
	}
	else
	{
		pid111 = fork();
		if (pid111 == -1)
			err_fork();
		process(data, pid111);
	}
	return ;
}

void	pre_exec(t_data *data)
{
	t_chunk	*chunk;

	chunk = data->chunk;
	if (chunk && !(chunk->next))
		exec(data);
	else
		execs(data, &data->chunk);
}
