/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:38:48 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/15 15:44:15 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	main(void)
{
	int	i;
	int	nb;
	int	nb1;

	const char *tests[] = {
		"42",                  // Simple positive number
		"-42",                 // Simple negative number
		"  \t \v \n \f 12345", // Number with leading whitespace
		" +123",               // Number with leading plus sign
		" --42",               // Invalid input with multiple minus signs
		"2147483647",          // INT_MAX
		"-2147483648",         // INT_MIN
		"2147483648",          // Overflow past INT_MAX
		"-2147483649",         // Underflow past INT_MIN
		"abc123",              // Invalid: alphabet before numbers
		"123abc",              // Numbers followed by invalid characters
		"",                    // Empty string
		" \t \n",              // Only whitespace
		"0",                   // Zero
		"00001234",            // Leading zeros
		"-00001234",           // Negative with leading zeros
		"+00001234",           // Positive with leading zeros
		NULL                   // End of tests
	};
	i = 0;
	while (tests[i])
	{
		nb = ft_atoi(tests[i]);
		nb1 = atoi(tests[i]);
		printf("Test #%d: \"%s\"\n", i + 1, tests[i]);
		printf("ft_atoi: %d\n", nb);
		printf("atoi:    %d\n\n", nb1);
		i++;
	}
	return (0);
}
