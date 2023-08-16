/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:15:04 by mkiflema          #+#    #+#             */
/*   Updated: 2023/07/27 18:14:19 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
		return (0);
}

// int main(){
// 	printf("%c", ft_isalpha('a' - 1));
// 	printf("\n%c", ft_isalpha('a'));
// 	printf("\n%c", ft_isalpha('z' + 1));
// 	printf("\n%c", ft_isalpha('A' - 1));
// 	printf("\n%c", ft_isalpha('A'));
// 	printf("\n%c", ft_isalpha('Z' + 1));
// 	printf("\n%c", ft_isalpha('Z' ));
// }