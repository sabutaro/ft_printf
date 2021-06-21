/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifstring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:16:55 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 11:59:53 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	go_dot(t_struct *f, int a)
{
	if (f->dot > 0 && f->dot <= a)
	{
		while (a > f->dot)
			a--;
	}
	else if (f->dot > a)
		f->dot = a;
	else
		return (0);
	return (a);
}

static int	go_width(t_struct *f, int a)
{
	while (a < f->width)
	{
		if (f->zero == 1)
			f->nprinted += write(1, "0", 1);
		else
			f->nprinted += write(1, " ", 1);
		f->width--;
	}
	return (a);
}

int	ifstring(va_list ap, t_struct *f)
{
	char	*str;
	int		a;

	if (!(str = va_arg(ap, char *)))
		str = "(null)";
	a = ft_strlen(str);
	if (f->dot >= 0)
		a = go_dot(f, a);
	if (f->width > 0 && f->minus == 0)
		a = go_width(f, a);
	f->nprinted += write(1, str, a);
	if (f->minus == 1)
	{
		while (a < f->width)
		{
			f->nprinted += write(1, " ", 1);
			f->width--;
		}
	}
	return (f->nprinted);
}
