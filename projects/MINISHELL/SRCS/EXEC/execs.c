/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 14:12:11 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	ft_close_all(int fd[3])
{
	char	buf;
	int		i;

	i = 4;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	while (i < 150)
	{
		if (read(i, &buf, 0) != -1)
			close(i);
		i++;
	}
}

void	processs(t_data *data, t_chunk *chunk, int fd[3])
{
	if (!chunk->prev)
		dup2(fd[1], STDOUT_FILENO);
	if (!chunk->next)
		dup2(fd[2], STDIN_FILENO);
	else if (chunk->next && chunk->prev)
	{
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_close_all(fd);
	if (!chunk->args)
	{
		redir(chunk);
		close(data->stdin);
		close(data->stdout);
		free_data_exec(data);
		rl_clear_history();
		exit (0) ;
	}
	else if (is_builtin(chunk->cmd))
	{
		redir(chunk);
		do_builtin(data, chunk, chunk->cmd);
		redir(chunk);
		close(data->stdin);
		close(data->stdout);
		free_data_exec(data);
		rl_clear_history();
		exit (0) ;
	}
	if (is_dot(data->chunk->cmd))
		return (free_data_exec(data));
	if (is_dir(data->chunk->cmd))
		return (free_data_exec(data));
	redir(chunk);
	exec_cmd(data, chunk->args, data->envcpy);
}

void	waitit(t_data *data)
{
	t_chunk	*chunk;
	int		status;

	chunk = (data->chunk);
	while (chunk)
	{
		waitpid(chunk->pid, NULL, 0);
		single_exit_s(WEXITSTATUS(status), UPDATE);
		chunk = chunk->next;
	}
}

void	swap_pipes(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

void	execs(t_data *data, t_chunk **chunk_lst)
{
	int		fd[3];
	t_chunk	*chunk;

	chunk = (*chunk_lst);
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	fd[2] = dup(STDIN_FILENO);
	while (chunk)
	{
		if (pipe(fd) != 0)
			err_pipe();
		chunk->pid = fork();
		if (chunk->pid == -1)
			err_fork();
		if (!chunk->pid)
			processs(data, chunk, fd);
		swap_pipes(fd);
		close(data->stdin);
		close(data->stdout);
		chunk = chunk->next;
	}
	close(fd[2]);
	waitit(data);
}
