/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:07:34 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:14:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*mcplc(char *s, char *env)
{
	char	*str;
	int		i;
	int		j;

	i = ft_strlen(s);
	j = 0;
	str = malloc(ft_strlen(env) - ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (env[i])
	{
		str[j] = env[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s);
	return (str);
}

char	*expand(char *s, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], s, (ft_strlen(s))) == 0)
		{
			str = mcplc(s, env[i]);
			return (str);
		}
		i++;
	}
	return (s);
}

char	*cplc(char *s, char **env)
{
	char	*str;
	char	*str2;
	int		i;

	i = 1;
	while (s[i] && s[i] != ' ' && s[i] != '$')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 1;
	while (s[i] && s[i] != ' ' && s[i] != '$')
	{
		str[i - 1] = s[i];
		i++;
	}
	str[i - 1] = '=';
	str[i] = '\0';
	str = expand(str, env);
	str2 = cplc2(s);
	if (ft_strcmp(str, str2) == 0)
		return (free(str2), free(str), s);
	free(str2);
	return (str);
}

char	*do_it(char *s, char *s1, char *str)
{
	char	*before;
	char	*after;
	char	*str3;

	before = str_before(s);
	after = str_after(s1);
	str3 = ft_strjoin(before, str);
	free(before);
	before = ft_strjoin(str3, after);
	free(after);
	free(str3);
	str3 = ft_strdup(before);
	free(before);
	free(s);
	return (str3);
}

char	*expande_moi(char *s, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (ft_strcmp("$?", s) == 0)
	{
		i = single_exit_s(0, RETRIEVE);
		free(s);
		s = ft_itoa(i);
		return (s);
	}
	while (s[i])
	{
		if (s[i] == '$') /*<--- if (strcmp($?,
				s) == 0) do single_exit(RETRIEVE)*/
		{
			str = cplc(&s[i], env);
			if (ft_strcmp(str, s) != 0)
				s = do_it(s, &s[i], str);
		}
		i++;
	}
	return (s);
}
