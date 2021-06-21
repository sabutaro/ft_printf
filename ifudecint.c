/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifudecint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:16:17 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 11:59:59 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				go_width_udecint(int width, int minus, int has_zero, t_struct *f)
{
	int char_count;

	char_count = 0;
	while (width - minus > 0)
	{
		if (has_zero)
			f->nprinted += write(1, "0", 1);
		else
			f->nprinted += write(1, " ", 1);
		width -= 1;
		char_count++;
	}
	return (char_count);
}

static int		put_flag_in_udecint(char *d_i, t_struct *f)
{
	int nb;

	nb = 0;
	if (f->dot >= 0)
		nb += go_width_udecint(f->dot - 1, ft_strlen(d_i) - 1, 1, f);
	f->nprinted += write(1, d_i, ft_strlen(d_i));
	return (nb);
}

static int		put_flag(char *d_i, t_struct *f)
{
	int	nb;

	nb = 0;
	if (f->minus == 1)
		nb += put_flag_in_udecint(d_i, f);
	if (f->dot >= 0 && (size_t)f->dot < ft_strlen(d_i))
		f->dot = ft_strlen(d_i);
	if (f->dot >= 0)
	{
		f->width -= f->dot;
		nb += go_width_udecint(f->width, 0, 0, f);
	}
	else
		nb += go_width_udecint(f->width, ft_strlen(d_i), f->zero, f);
	if (f->minus == 0)
		nb += put_flag_in_udecint(d_i, f);
	return (nb);
}

int				ifudecint(va_list ap, t_struct *f)
{
	unsigned int	nb_unsi;
	int				nb_int;
	char			*c;

	nb_unsi = va_arg(ap, unsigned int);
	nb_int = (unsigned int)(4294967295 + 1 + nb_unsi);
	c = ft_u_itoa(nb_int);
	if (f->dot == 0 && nb_int == 0)
	{
		go_width_udecint(f->width, 0, 0, f);
		return (f->nprinted);
	}
	put_flag(c, f);
	free(c);
	return (f->nprinted);
}
