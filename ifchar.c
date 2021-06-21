/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:17:18 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 11:59:31 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		go_width_char(t_struct *f, int a)
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

int		ifchar(va_list ap, t_struct *f)
{
	int	nb;
	int	c;

	c = 0;
	nb = va_arg(ap, int);
	if (f->minus == 1)
		f->nprinted += write(1, &nb, 1);
	c = go_width_char(f, 1);
	if (f->minus == 0)
		f->nprinted += write(1, &nb, 1);
	return (f->nprinted + 1);
}
