/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brcaetan <brcaetan@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:33:08 by brcaetan          #+#    #+#             */
/*   Updated: 2023/01/27 23:32:12 by brcaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Putstr, Putnbr_pointer, Putnbr_base
static int	ft_putstr(const char *src)
{
	int	i;

	i = 0;
	if (!src)
	{
		ft_putstr("(null)");
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	ft_putnbr_base(const char *base, long long int nbr, int size)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
		i++;
	}
	if (nbr / size > 0)
	{
		i += ft_putnbr_base(base, (nbr / size), size);
	}
	write(1, &base[nbr % size], 1);
	i++;
	return (i);
}

static int	ft_putnbr_pointer(const char *base, unsigned long long nbr,
		int size, int flag)
{
	int	i;

	i = 0;
	if (nbr == 0)
		write(1, "(nil)", 5);
	if (flag == 0)
		i += ft_putstr("0x");
	if (nbr / size > 0)
	{
		i += ft_putnbr_pointer(base, (nbr / size), size, 0);
	}
	write(1, &base[nbr % size], 1);
	i++;
	return (i);
}

// Format Function
static int	format(const char src, va_list args)
{
	int	i;
	int	j;

	i = 1;
	if (src == 'c')
	{
		j = va_arg(args, int);
		write(1, &j, 1);
	}
	else if (src == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (src == 'p')
		i = ft_putnbr_pointer("0123456789ABCDEF", va_arg(args, long int), 16,
				0);
	else if (src == 'd' || src == 'i')
		i = ft_putnbr_base("0123456789", va_arg(args, long int), 10);
	else if (src == 'u')
		i = ft_putnbr_base("0123456789", va_arg(args, unsigned int), 10);
	else if (src == 'x')
		i = ft_putnbr_base("0123456789abcdef", va_arg(args, unsigned int), 16);
	else if (src == 'X')
		i = ft_putnbr_base("0123456789ABCDEF", va_arg(args, unsigned int), 16);
	else if (src == '%')
		write(1, "%%", 1);
	return (i);
}

int	ft_printf(const char *src, ...)
{
	va_list	args;
	int		prtcont;

	prtcont = 0;
	va_start(args, src);
	while (*src)
	{
		if (src != '%')
		{
			write(1, &src, 1);
			prtcont++;
		}
		else
		{
			src++;
			prtcont += format(*src, args);
		}
		src++;
	}
	va_end(args);
	return (prtcont);
}
