/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:03 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/13 13:49:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	char	*str;
	int	ret1, ret2;

	str = NULL;
	printf("Hello %c%c%c%c%c%c", 'w', 'o', 'r', 'l', 'd', '\n');
	ft_printf("Hello %c%c%c%c%c%c", 'w', 'o', 'r', 'l', 'd', '\n');

	printf("Hello %c %c %c %c %c %c", '1', '2', '3', '4', '5', '\n');
	ft_printf("Hello %c %c %c %c %c %c", '1', '2', '3', '4', '5', '\n');

	printf("salut %s", "ca va?\n");
	ft_printf("salut %s", "ca va?\n");

	printf("salut %s %s", "ca va?", "Oui et toi?\n");
	ft_printf("salut %s %s", "ca va?", "Oui et toi?\n");

	printf("les pointer %p %p %p %p %p %c", "14", "24", "168", "0", str, '\n');
	ft_printf("les pointer %p %p %p %p %p %c", "19", "24", "168", "0", str,'\n');

	printf("%d %d %d %i %i %i %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');
	ft_printf("%d %d %d %i %i %i %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');

	printf("%u %u %u %u %u %u %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');
	ft_printf("%u %u %u %u %u %u %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');

	printf("%x %x %x %X %X %X %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');
	ft_printf("%x %x %x %X %X %X %c", 1, 125, 2147483647, -1, -125, -2147483647,'\n');

	    ret1 = ft_printf("Hello %c%c%c%c%c\n", 'w', 'o', 'r', 'l', 'd');
    ret2 = printf("Hello %c%c%c%c%c\n", 'w', 'o', 'r', 'l', 'd');
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("Hello %c %c %c %c %c\n", '1', '2', '3', '4', '5');
    ret2 = printf("Hello %c %c %c %c %c\n", '1', '2', '3', '4', '5');
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("salut %s\n", "ca va?");
    ret2 = printf("salut %s\n", "ca va?");
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("salut %s %s\n", "ca va?", "Oui et toi?");
    ret2 = printf("salut %s %s\n", "ca va?", "Oui et toi?");
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("les pointer %p %p %p %p %p\n", (void *)"14", (void *)"24", (void *)"168", (void *)"0", (void *)str);
    ret2 = printf("les pointer %p %p %p %p %p\n", (void *)"14", (void *)"24", (void *)"168", (void *)"0", (void *)str);
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("%d %d %d %i %i %i\n", 1, 125, 2147483647, -1, -125, -2147483647);
    ret2 = printf("%d %d %d %i %i %i\n", 1, 125, 2147483647, -1, -125, -2147483647);
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("%u %u %u %u %u %u\n", 1, 125, 2147483647, (unsigned)-1, (unsigned)-125, (unsigned)-2147483647);
    ret2 = printf("%u %u %u %u %u %u\n", 1, 125, 2147483647, (unsigned)-1, (unsigned)-125, (unsigned)-2147483647);
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("%x %x %x %X %X %X\n", 1, 125, 2147483647, (unsigned)-1, (unsigned)-125, (unsigned)-2147483647);
    ret2 = printf("%x %x %x %X %X %X\n", 1, 125, 2147483647, (unsigned)-1, (unsigned)-125, (unsigned)-2147483647);
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    ret1 = ft_printf("nombre de caracteres print %x\n", 125);
    ret2 = printf("nombre de caracteres print %x\n", 125);
    printf("ft_printf: %d, printf: %d\n", ret1, ret2);

    return(0);
}
