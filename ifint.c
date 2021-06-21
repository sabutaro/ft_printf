/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 13:57:04 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 12:50:11 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			go_width_int(int width, int minus, int has_zero, t_struct *f)
{
	int	char_count;

	char_count = 0;
	while (width - minus > 0)
	{
		if (has_zero && f->minus == 1 && f->zero == 1 && f->star == 1 
				&& f->dot < 0)
			f->nprinted += write(1, " ", 1);
		else if (has_zero)
			f->nprinted += write(1, "0", 1);
		else
			f->nprinted += write(1, " ", 1);
		width -= 1;
		char_count++;
	}
	return (char_count);
}

static int	put_flag_in_int(char *str, int keep_nb, t_struct *f)
{
	int	nb;

	nb = 0;
	if (keep_nb < 0 && f->dot >= 0)
		f->nprinted += write(1, "-", 1);
	if (f->dot >= 0)
		nb += go_width_int(f->dot - 1, ft_strlen(str) - 1, 1, f);
	f->nprinted += write(1, str, ft_strlen(str));
	return (nb);
}

static int	put_flag(char *str, int keep_nb, t_struct *f)
{
	int	nb;

	nb = 0;
	if (f->minus == 1)
		nb += put_flag_in_int(str, keep_nb, f);
	if (f->dot >= 0 && (size_t)f->dot < ft_strlen(str))
		f->dot = ft_strlen(str);
	if (f->dot >= 0)
	{
		f->width -= f->dot;
		nb += go_width_int(f->width, 0, 0, f);
	}
	else
		nb += go_width_int(f->width, ft_strlen(str), f->zero, f);
	if (f->minus == 0)
		nb += put_flag_in_int(str, keep_nb, f);
	return (nb);
}

int			ifint(t_struct *f, va_list ap)
{
	char	*str;
	int		keep_nb;
	int		nb;

	nb = va_arg(ap, int);
	keep_nb = nb;
	if (f->dot == 0 && nb == 0)
	{
		go_width_int(f->width, 0, 0, f);
		return (f->nprinted);
	}
	if (nb < 0 && (f->dot >= 0 || f->zero == 1))
	{
		if (nb == -2147483648)
		{
			f->nprinted += write(1, "-2147483648", 11);
			return(f->nprinted);
		}
		if (f->zero == 1 && f->dot < 0)
			f->nprinted += write(1, "-", 1);
		nb *= -1;
		f->zero = 1;
		f->width--;
	}
	str = ft_itoa(nb);
	put_flag(str, keep_nb, f);
	free(str);
	return (f->nprinted);
}
