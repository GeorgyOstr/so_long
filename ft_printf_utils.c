/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:06:55 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/10 22:06:22 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	int	res;

	res = 0;
	while (res == 0)
		res = write(1, &c, 1);
	if (res < 0)
		return (-100);
	return (res);
}

int	ft_putstr(const char *s)
{
	long	i;
	long	res;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	while (*s)
	{
		res = ft_putchar(*(s++));
		i += res;
		if (res < 0 || i > INT_MAX)
			return (-100);
	}
	return (i);
}

int	ft_putnbr(long n)
{
	int	ans;

	ans = 0;
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		ans += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ans += ft_putnbr(n / 10);
	ans += ft_putchar(n % 10 + '0');
	return (ans);
}

int	ft_puthex(unsigned long n, char c)
{
	int		ans;

	ans = 0;
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 16)
		ans += ft_puthex(n / 16, c);
	if (c == 'x')
		ans += ft_putchar("0123456789abcdef"[n % 16]);
	else
		ans += ft_putchar("0123456789ABCDEF"[n % 16]);
	return (ans);
}

int	ft_putptr(const void *s)
{
	if (!s)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_puthex((unsigned long)s, 'x'));
}
