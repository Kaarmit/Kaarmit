/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:46:42 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/01 17:58:20 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*s2;
	int	i = 0;
	int	length;

	length = ft_strlen(src);

	s2 = malloc (sizeof(char) * (length + 1));
	if (s2 == NULL)
		return (NULL);
	while (src[i])
	{	
		s2[i] = src[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
#include <stdio.h>
#include <string.h>

char *ft_strdup(char *src);

int	main(void)
{
	printf("%s\n", strcmp(strdup("Test"), ft_strdup("Test")) == 0 ?
			"OK" :
			"Fail");
	printf("%s\n", strcmp(strdup("484df41hdy1h111fs1fsd15sf15sdf115d15fdgs15gfd4sg1615df156g1515g4erg4561esg156gr15156g15eg15eg15e51e51g1515ge156e156eg156e15156ge516e1551eg51eg15g1551eg15e516eg15e15eg1515e55eg51e15e51g5151eg15eg1515egr515151erg51er51e51e551ee5eg51egr51er51er5er5eg51e5r1e51rg5egr5eg51erg5e1r51e6rg51egr516ee5g15e1g5e1g5e1g51ger51egr51erg55reg5er55er55"), ft_strdup("484df41hdy1h111fs1fsd15sf15sdf115d15fdgs15gfd4sg1615df156g1515g4erg4561esg156gr15156g15eg15eg15e51e51g1515ge156e156eg156e15156ge516e1551eg51eg15g1551eg15e516eg15e15eg1515e55eg51e15e51g5151eg15eg1515egr515151erg51er51e51e551ee5eg51egr51er51er5er5eg51e5r1e51rg5egr5eg51erg5e1r51e6rg51egr516ee5g15e1g5e1g5e1g51ger51egr51erg55reg5er55er55")) == 0 ?
			"OK" :
			"Fail");
}

