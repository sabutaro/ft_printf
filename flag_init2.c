/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:26:06 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 13:01:05 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			dot(const char *format, int start, t_struct *f, va_list ap)
{
	int	i;

	i = start;
	i++;
	if (format[i] == '*')
	{
		f->dot = va_arg(ap, int);
		i++;
	}
	else
	{
		f->dot = 0;
		while (ft_isdigit(format[i]))
			f->dot = (f->dot * 10) + (format[i++] - '0');
	}
	return (i);
}

void		flag_digit(char c, t_struct *f)
{
	f->width = (f->width * 10) + (c - '0');
	return ;
}

void		flag_star(va_list ap, t_struct *f)
{
	f->star = 1;
	f->width = va_arg(ap, int);
	if (f->width < 0)
	{
		f->minus = 1;
		f->width *= -1;
	}
}

void		if_up_or_not(char c, t_struct *f)
{
	if (c == 'X')
		f->up = 1;
	return ;
}
