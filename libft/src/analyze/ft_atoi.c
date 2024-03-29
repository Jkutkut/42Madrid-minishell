/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:34 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/27 22:09:59 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

#define SPACES " \n\v\f\r\t"

int	ft_hasany(const char *str, char c);
int	ft_isdigit(int c);

/**
 * @brief Converts a string to an integer.
 * 
 * @param str String to convert.
 * @return int Number representing the string.
 */
int	ft_atoi(char *str)
{
	size_t	number;
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_hasany(SPACES, str[i]))
		i++;
	if (ft_hasany("+-", str[i]))
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		number *= 10;
		number += (str[i++] - 48);
	}
	if (number > LONG_MAX && sign < 0)
		return (0);
	else if (number > LONG_MAX && sign > 0)
		return (-1);
	return (sign * number);
}
