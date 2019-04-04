/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:58:03 by nkellum           #+#    #+#             */
/*   Updated: 2019/04/04 14:09:48 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int contains(char *str, char c)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while(str[i])
	{
		if(str[i] == c)
			num++;
		i++;
	}
	return (num);
}

char check_format(char *fmt)
{
	int i;
	int valid;
	char *formats;
	char *flags;

	i = 0;
	valid = 1;
	formats = "cspdiouxXf";
	flags = " .#0123456789-+hl";
	while(fmt[i] && valid)
	{
		if(contains(formats, fmt[i]))
			return (fmt[i]);
		if(!contains(flags, fmt[i]))
			return ('\0');
		i++;
	}
	return ('\0');
}



void analyse_format(va_list ap, char *fmt, char c, t_flags *flags)
{
	int i;
	char *str_formats;

	init_flags(flags);
	flags->fmt_str = ft_strsub(fmt, 0, ft_strchr(fmt, c) - fmt);
	flags->fmt_char = c;
	flags->h = contains(flags->fmt_str, 'h');
	flags->l = contains(flags->fmt_str, 'l');
	get_flags(flags);
	i = 0;
	str_formats = "cs";
	if(contains(str_formats, c))
	{
		flags->is_str = 1;
		print_string(ap, flags);

	}
	else
	{
		flags->is_str = 0;
		print_num(ap, flags);
	}
}


int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int d;
	char c, *s;
	t_flags *flags;

	if((flags = malloc(sizeof(t_flags))) == NULL)
		return 0;

  va_start(ap, fmt);
  while (*fmt)
  {
	  if(*fmt == '%')
	  {
		  fmt++;
			c = check_format(fmt);
			if(*fmt == '%')
				ft_putchar('%');
		  	else if(c != '\0')
			{
				analyse_format(ap, fmt, c, flags);
				fmt += ft_strchr(fmt, c) - fmt;
			}
			else
				ft_putchar(*fmt);
	  }
	  else
	  	ft_putchar(*fmt);
	fmt++;
  }
  	free(flags);
    va_end(ap);
	return (16);
}

//
// int main()
// {
// 	int fieldwidth = 10;
// 	float flt = .123;
// 	unsigned long long num = 161216121612161212;
// 	//void *ptr = &flt;
// 	//char *str = ft_itoa_base(num, 16);
// 	//long long i = (char) num;
// 	//char *str = ft_itoa_base(4294843841, 8);
// 	//long long i = ft_atoi_base(ft_itoa_base(4294843841, 8), 10);
// 	//char *str =
//
// 	//printf(0"%s %010o\n", ft_itoa_base(num, 16), num);
// 	//ft_printf("12345678901234567890\n");
// 	printf("%lf\n", flt);
// 	ft_printf("%f\n", flt);
//
// 	//ft_printf("%llo\n", num);
//
//
// }
