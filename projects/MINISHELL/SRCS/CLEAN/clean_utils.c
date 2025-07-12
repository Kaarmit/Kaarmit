/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:55:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 14:00:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	**malloc_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	free_envcpy(char **envcpy)
{
	int	i;

	i = 0;
	while (envcpy[i])
	{
		free(envcpy[i]);
		i++;
	}
	free(envcpy);
}

void	free_data(t_data *data)
{
	if (!data)
		exit(EXIT_SUCCESS);
	if (data->tokens)
		malloc_free(data->tokens);
	if (data->token)
		free_lst(data->token);
	if (data->brut_input)
		free(data->brut_input);
	if (data->envcpy)
		free_envcpy(data->envcpy);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
	if (data->env)
		clear_env_lst(&data->env);
	close(data->stdin);
	close(data->stdout);
	free(data);
	exit(EXIT_SUCCESS);
}

void	free_data_exit(t_data *data)
{
	if (!data)
		exit(EXIT_SUCCESS);
	if (data->brut_input)
		free(data->brut_input);
	if (data->envcpy)
		free_envcpy(data->envcpy);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
	if (data->env)
		clear_env_lst(&data->env);
	close(data->stdin);
	close(data->stdout);
	free(data);
	// exit(EXIT_SUCCESS);
}

void	free_data_bis(t_data *data)
{
	if (!data)
	{
		printf("data is NULL\n");
		close(data->stdin);
		close(data->stdout);
		exit(EXIT_SUCCESS);
	}
	if (data->tokens)
		malloc_free(data->tokens);
	if (data->token)
		free_lst(data->token);
	if (data->brut_input)
		free(data->brut_input);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
}

void	free_data_exec(t_data *data)
{
	if (!data)
	{
		printf("data is NULL\n");
		exit(EXIT_SUCCESS);
	}
	// if (data->brut_input)
	// 	free(data->brut_input);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
}

void	clean_program(t_data *data)
{
	free_data(data);
	// clear_env_lst(&data->env);
	rl_clear_history();
}
