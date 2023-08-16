/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:56:14 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/29 19:50:42 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i])
		return (1);
	else if (s2[i])
		return (1);
	else
		return (0);
}

// int main()
// {
// 	char	*s1 = "x12";
// 	char	*s2 = "x12";
// 	printf("%d", strcmp(s1, s2));
// 	printf("\n%d", ft_strcmp(s1, s2));
// }