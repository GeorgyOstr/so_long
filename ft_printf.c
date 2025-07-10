/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:06:55 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/10 22:05:43 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_switch(const char *str, int *i, va_list *args)
{
	int	ans;

	ans = 0;
	if (!str[++(*i)])
		return (ans);
	else if (str[*i] == '%')
		ans += ft_putchar('%');
	else if (str[*i] == 'c')
		ans += ft_putchar((char)va_arg(*args, int));
	else if (str[*i] == 's')
		ans += ft_putstr(va_arg(*args, char *));
	else if (str[*i] == 'p')
		ans += ft_putptr(va_arg(*args, void *));
	else if (str[*i] == 'd' || str[*i] == 'i')
		ans += ft_putnbr(va_arg(*args, int));
	else if (str[*i] == 'u')
		ans += ft_putnbr(va_arg(*args, unsigned int));
	else if ((str[*i] == 'x') || (str[*i] == 'X'))
		ans += ft_puthex(va_arg(*args, unsigned int), str[*i]);
	else
		return (-100);
	(*i)++;
	return (ans);
}

static int	check_increment(int ans, int val)
{
	long	lans;

	lans = ans;
	lans += val;
	if (val < 0 || lans > INT_MAX)
		return (-100);
	return (ans + val);
}

static int	ret_end(int a, va_list *args)
{
	va_end(*args);
	return (a);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		ans;

	if (!str)
		return (-1);
	i = 0;
	ans = 0;
	va_start(args, str);
	while (str[i])
	{
		while (str[i] && str[i] != '%')
		{
			ans = check_increment(ans, ft_putchar(str[i++]));
			if (ans < 0)
				return (ret_end(-1, &args));
		}
		if (str[i] && str[i] == '%')
		{
			ans = check_increment(ans, ft_switch(str, &i, &args));
			if (ans < 0)
				return (ret_end(-1, &args));
		}
	}
	return (ret_end(ans, &args));
}
