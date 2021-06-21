/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:45:08 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 13:00:49 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct	*flag_init(t_struct *f)
{
	f->nprinted = 0;
	f->dot = -1;
	f->width = 0;
	f->zero = 0;
	f->minus = 0;
	f->up = 0;
	f->star = 0;
	return (f);
}

void		flag_minus(t_struct *f)
{
	f->minus = 1;
	f->zero = 0;
}

int			tlist(int c)
{
	return ((c == 'c') || (c == 's') || (c == 'p') || (c == 'd') || (c == 'i')
			|| (c == 'u') || (c == 'x') || (c == 'X') || (c == '%'));
}

int			flist(int c)
{
	return ((c == '-') || (c == ' ') || (c == '0') || (c == '.') || (c == '*'));
}

void		flag_reinit(t_struct *f)
{
	f->dot = -1;
	f->width = 0;
	f->zero = 0;
	f->minus = 0;
	f->up = 0;
	f->star = 0;
}
