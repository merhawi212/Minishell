/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:58:35 by mkiflema          #+#    #+#             */
/*   Updated: 2023/07/11 13:22:41 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c > 255)
		c = c / 256;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}

// int main()
// {
// 	char s[] = "tripouille";
// 	// char c = ;
// 	printf("%s",strchr(s, 't' + 255));
// 	printf("\n%s", ft_strchr(s, 't' + 255));
// }