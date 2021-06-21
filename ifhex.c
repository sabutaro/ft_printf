/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifhex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:17:14 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 11:59:30 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			go_width_hex(int width, int minus, int has_zero, t_struct *f)
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

static int	put_flag(char *hex, t_struct *f)
{
	int	nb;

	nb = 0;
	if (f->minus == 1)
	{
		if (f->dot >= 0)
			nb += go_width_hex(f->dot - 1, ft_strlen(hex) - 1, 1, f);
		f->nprinted += write(1, hex, ft_strlen(hex));
	}
	if (f->dot >= 0 && (size_t)f->dot < ft_strlen(hex))
		f->dot = ft_strlen(hex);
	if (f->dot >= 0)
	{
		f->width -= f->dot;
		nb += go_width_hex(f->width, 0, 0, f);
	}
	else
		nb += go_width_hex(f->width, ft_strlen(hex), f->zero, f);
	if (f->minus == 0)
		{
			if (f->dot >= 0)
				nb += go_width_hex(f->dot - 1, ft_strlen(hex) - 1, 1, f);
			f->nprinted += write(1, hex, ft_strlen(hex));
		}
	return (nb);
}

int			ifhex(va_list ap, t_struct *f)
{
	char				*str;
	unsigned int		nb;
	int					i;

	i = -1;
	nb = va_arg(ap, unsigned int);
	str = ft_ptoa(nb);
	if (f->up == 1)
		while (str[++i])
			str[i] = ft_toupper(str[i]);
	if (f->dot == 0 && nb == 0)
	{
		go_width_hex(f->width, 0, 0, f);
		return (f->nprinted);
	}
	put_flag(str, f);
	free(str);
	return (f->nprinted);
}
