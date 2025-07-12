/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:53:36 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 16:40:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_exp_arg(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (str[0] == '\'' && str[len - 1] == '\'');
}

int	is_quoted_arg(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (str[0] == '"' && str[len - 1] == '"');
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (str[i] == '\0');
}
