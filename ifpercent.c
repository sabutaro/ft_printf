/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifpercent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:45:13 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 11:59:44 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ifpercent(t_struct *f)
{
	int a;

	a = 1;
	if (f->width > 0 && f->minus == 0)
	{
		while (a < f->width)
		{
			if (f->zero == 1)
				f->nprinted += write(1, "0", 1);
			else
				f->nprinted += write(1, " ", 1);
			f->width--;
		}
	}
	f->nprinted += write(1, "%", 1);
	if (f->minus == 1 && f->width > 0)
	{
		while (a < f->width-- && a >= 0)
			f->nprinted += write(1, " ", 1);
	}
	return (f->nprinted);
}
