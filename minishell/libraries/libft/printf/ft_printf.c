/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:48:37 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 12:48:58 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_printf_arg(const char *fmt, int i, va_list ap, int *ret)
{
	if (fmt[i + 1] == '%')
		*ret += ft_putchar_fd(fmt[i + 1], 1);
	else if (fmt[i + 1] == 'c')
		*ret += ft_putchar_fd(va_arg(ap, int ), 1);
	else if (fmt[i + 1] == 's')
		*ret += ft_putstr_fd(va_arg(ap, char *), 1);
	else if (fmt[i + 1] == 'd' || fmt[i + 1] == 'i')
		*ret += ft_putnbr_fd(va_arg(ap, int), 1);
	else if (fmt[i + 1] == 'u')
		*ret += putnbr_u(va_arg(ap, unsigned int));
	else if (fmt[i + 1] == 'x' || fmt[i + 1] == 'X')
	{
		if (fmt[i + 1] == 'X')
			*ret += put_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
		else
			*ret += put_hex(va_arg(ap, unsigned int), "0123456789abcdef");
	}
	else if (fmt[i + 1] == 'p')
		*ret += put_pointer(va_arg(ap, void *));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			ft_printf_arg(format, i, ap, &ret);
			i++;
		}
		else
			ret += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}
