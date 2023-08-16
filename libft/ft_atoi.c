/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:29:11 by mkiflema          #+#    #+#             */
/*   Updated: 2023/07/27 16:39:35 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] != '\0' && (nptr[i] == ' '
			|| (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else
	{
		if (nptr[i] == '+')
			i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
		result = (result * 10) + (nptr[i++] - '0');
	return (sign * result);
}

// #include <stdio.h>

// int main()
// {
// 	char *str ="-9223372036854775809";
// 	printf("%d", atoi(str));
// 	printf("\n%d", ft_atoi(str));
// }