/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifpointeur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:17:03 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 16:26:33 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		get_digit2(int n)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	return (n - 10 + 'a');
}

static char		*ft_ptoa2(unsigned long long p)
{
	unsigned long long	tmpn;
	unsigned long long 	n;
	int					len;
	char				*str;

	n = (unsigned long long)p;
	tmpn = (unsigned long long)p;
	len = 2;
	while (tmpn /= 16)
		len++;
	if ((str = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = get_digit2(n % 16);
		n = n / 16;
	}
	return (str);
}

int				go_width_pointeur(int width, int minus, int has_zero, t_struct *f)
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

static int		put_flag_pointeur(char *str, t_struct *f)
{
	int char_count;
	int i;

	i = 0;
	char_count = 0;
	f->nprinted += write(1, "0x", 2);
	if (f->dot >= 0 && str[i] == '0')
	{
		char_count += go_width_pointeur(f->dot, ft_strlen(str), 1, f);
		f->nprinted += write(1, str, 1);
	}
	else if (f->dot >= 0 && f->dot > f->width)
	{
		char_count += go_width_pointeur(f->dot, ft_strlen(str), 1, f);
		f->nprinted += write(1, str, ft_strlen(str));
	}
	else if (f->dot >= 0)
	{
		char_count += go_width_pointeur(f->dot, ft_strlen(str), 1, f);
		f->nprinted += write(1, str, f->dot);
	}
	else
		f->nprinted += write(1, str, ft_strlen(str));
	return (char_count);
}

int				ifpointeur(va_list ap, t_struct *f)
{
	void	*p;
	char				*str;
	int					a;

	a = 0;
	p = va_arg(ap, void *);
	str = ft_ptoa2((unsigned long long)p);
	if (p == 0 && f->dot == 0)
	{
		a += go_width_pointeur(f->width, 2, 0, f);
		f->nprinted += write(1, "0x", 2);
		return (f->nprinted);
	}
	if ((size_t)f->dot < ft_strlen(str))
		f->dot = ft_strlen(str);
	if (f->minus == 1)
		a += put_flag_pointeur(str, f);
	a += go_width_pointeur(f->width, ft_strlen(str) + 2, 0, f);
	if (f->minus == 0)
		a += put_flag_pointeur(str, f);
	free(str);
	return (f->nprinted);
}
