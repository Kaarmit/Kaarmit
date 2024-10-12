/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:07:27 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/09 17:09:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_list
{
	struc s_list	*next;
	void			*data;
}					t_list;

void	ft_list_foreach(t_list *beging_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}
