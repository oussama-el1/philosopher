/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:18:40 by oel-hadr          #+#    #+#             */
/*   Updated: 2025/03/18 10:24:24 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow_hdl(int num, int next, int sign)
{
	if (sign == 1)
		if ((num >= (INT_MAX / 10) && next > 7) || num > (INT_MAX / 10))
			return (-1);
	if (sign == -1)
		if ((num >= -(INT_MIN / 10) && next > 8) || num > -(INT_MIN / 10))
			return (0);
	return (1);
}

static int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	int				overflow;
	unsigned long	result;

	sign = 1;
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		overflow = overflow_hdl(result, (str[i] - '0'), sign);
		if (overflow != 1)
			return (INT_MIN);
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
