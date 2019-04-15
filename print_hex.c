/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:13:38 by nkellum           #+#    #+#             */
/*   Updated: 2019/04/15 17:32:35 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void print_field_hex(t_flags *flags, int length)
{
	int i;
	int zero_x;

	zero_x = (flags->hash && flags->fmt_char == 'x' && flags->i != 0) ? 2 : 0;
	i = 0;
	while(i < (flags->field_length - zero_x - length
		- flags->precision_dot *
		(flags->precision_val - length < 0 ?
			0 : flags->precision_val - length)))
	{
		if(flags->pad_zero)
			ft_putchar('0', flags);
		else
			ft_putchar(' ', flags);
		i++;
	}
}

void print_precision_hex(t_flags *flags, int length)
{
	int i;

	i = 0;
	//printf("length in prnt prec is %d\n", length);
	while(i < flags->precision_val - length * (flags->i > 0))
	{
		ft_putchar('0', flags);
		i++;
	}
}

int check_hex_format(va_list ap, t_flags *flags)
{
	void *ptr;

	if(flags->fmt_char == 'p')
	{
		ptr = va_arg(ap, void *);
		flags->i = (long long) ptr;
	}
	else
	{
		if(flags->l == 1)
			flags->i = va_arg(ap, unsigned long);
		else if(flags->l > 1)
			flags->i = va_arg(ap, unsigned long long);
		else
			flags->i = va_arg(ap, unsigned int);
	}
	if(flags->precision_dot && !flags->precision_val
		&& flags->i == 0 && flags->fmt_char != 'p')
	{
		while((flags->i)++ < flags->field_length)
			ft_putchar(' ', flags);
		return (0);
	}
	return (1);
}

void print_zero_x(t_flags *flags)
{
	if(flags->fmt_char == 'p')
		ft_putstr("0x", flags);
	if(flags->h == 1 && flags->fmt_char != 'p')
		flags->i = (unsigned short int) flags->i;
	if(flags->h >= 2 && flags->fmt_char != 'p')
		flags->i = (unsigned char) flags->i;
	if(flags->hash && flags->fmt_char == 'x' && flags->i != 0)
		ft_putstr("0x", flags);
	if(flags->hash && flags->fmt_char == 'X' && flags->i != 0)
		ft_putstr("0X", flags);
}

void print_hex(va_list ap, t_flags *flags)
{
	int length;

	if(!check_hex_format(ap, flags))
		return ;
	length = ft_strlen(ft_utoa_base(flags->i, 16, 0));
	if(flags->fmt_char == 'p' && flags->field_length > flags->precision_val)
		length += 2;
	if(flags->pad_zero)
		print_zero_x(flags);
	if(!flags->left_adjustment)
		print_field_hex(flags, length);
	if(!flags->pad_zero)
		print_zero_x(flags);
	print_precision_hex(flags, length);
	if(flags->fmt_char == 'x' || (flags->i > 0 && flags->fmt_char == 'p')
|| (flags->fmt_char == 'p' && !flags->precision_dot))
		ft_putstr(ft_utoa_base(flags->i, 16, 1), flags);
	else if(!(flags->i == 0 && flags->fmt_char == 'p'))
		ft_putstr(ft_utoa_base(flags->i, 16, 0), flags);
	if(flags->left_adjustment)
		print_field_hex(flags, length);
}
