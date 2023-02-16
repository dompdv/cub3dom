/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:44:53 by iazimzha          #+#    #+#             */
/*   Updated: 2021/12/08 11:47:13 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int nbr);
static char	*get_digit(int n, int n_len, char *str);

char	*ft_itoa(int n)
{
	char	*str;
	int		n_len;

	n_len = get_len(n);
	str = (char *) ft_calloc(n_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		*str = n / 10 + '0';
	else if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_strlcpy(str, "-2147483648", n_len + 1);
			return (str);
		}
		str[0] = '-';
		n *= -1;
	}
	str = get_digit(n, n_len, str);
	return (str);
}

static int	get_len(int nbr)
{
	int	nbr_len;

	nbr_len = 0;
	if (nbr <= 0)
		nbr_len++;
	while (nbr)
	{
		nbr /= 10;
		nbr_len++;
	}
	return (nbr_len);
}

static char	*get_digit(int n, int n_len, char *str)
{
	int	n1;

	n1 = 0;
	while (n != 0)
	{
		n_len--;
		n1 = n % 10;
		*(str + n_len) = n1 + '0';
		n = n / 10;
	}
	return (str);
}
