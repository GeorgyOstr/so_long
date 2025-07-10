/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:13:37 by gostroum          #+#    #+#             */
/*   Updated: 2025/07/10 22:06:00 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>

int	ft_putchar(char c);
int	ft_putstr(const char *s);
int	ft_putnbr(long n);
int	ft_puthex(unsigned long n, char c);
int	ft_putptr(const void *s);

int	ft_printf(const char *str, ...);

#endif
