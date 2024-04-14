/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoibase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:17:18 by aarmitan          #+#    #+#             */
/*   Updated: 2024/04/04 17:40:46 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

int    baseisvalid(char c, int base)
{
    char digits[17] = "0123456789abcdef";
    char digits2[17] = "0123456789ABCDEF";
    
    while (base--)
    {
        if(digits[base] == c || digits2[base] == c)
            return (1);
    }
    return (0);
}

int    value_of(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    else if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    else if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    return (0);
}

int    atoi_base(const char *str, int str_base)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == 32 || str[i] >= 9 && str[i] <= 13)
        i++;
    
    if (str[i] == '+')
        i++;

    if (str[i] == '-')
    {
        sign = sign * (-1);
        i++;
    }
    
    while (baseisvalid(str[i], str_base))
    {
        result = result * str_base + value_of(str[i]);
        i++;
    }
    return (result * sign);
}
```
