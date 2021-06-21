/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:37:43 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 13:01:24 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conversions(char c, va_list ap, t_struct *f)
{
	if (c == 'c')
		ifchar(ap, f);
	if (c == 's')
		ifstring(ap, f);
	if (c == 'p')
		ifpointeur(ap, f);
	if (c == 'd' || c == 'i')
		ifint(f, ap);
	if (c == 'u')
		ifudecint(ap, f);
	if (c == 'x' || c == 'X')
	{
		if_up_or_not(c, f);
		ifhex(ap, f);
	}
	if (c == '%')
		ifpercent(f);
}

int			modifiers(const char *fo, t_struct *f, va_list ap, int pos)
{
	while (fo[pos])
	{
		if (!ft_isdigit(fo[pos]) && !tlist(fo[pos]) && !flist(fo[pos]))
			break ;
		if (fo[pos] == '0' && f->width == 0)
			f->zero = 1;
		if (fo[pos] == '*')
			flag_star(ap, f);
		if (fo[pos] == '.')
			pos = dot(fo, pos, f, ap);
		if (fo[pos] == '-')
			flag_minus(f);
		if (ft_isdigit(fo[pos]))
			flag_digit(fo[pos], f);
		if (ft_strchr("cspdiouxX%", fo[pos]))
		{
			conversions(fo[pos], ap, f);
			break ;
		}
		if (fo[pos + 1] == '\0')
			break ;
		pos++;
	}
	return (pos);
}

int			parsel2(t_struct *f, int pos, const char *format, va_list ap)
{
	f->i = pos;
	if (ft_strchr("cspdiouxX%", format[pos]))
		conversions(format[pos], ap, f);
	return (f->i);
}

int			pf_parse_format(const char *fo, va_list ap, t_struct *f, int pos)
{
	while (fo[pos] != '\0')
	{
		flag_reinit(f);
		if (fo[pos] != '%' && fo[pos])
			f->nprinted += write(1, &fo[pos], 1);
		if (fo[pos] == '%' && fo[pos + 1])
		{
			while (ft_strchr(ALLSYMBOLS, fo[pos + 1]))
			{
				pos = pos + 1;
				if (fo[pos] == '\0')
					break ;
				if (ft_strchr("cspdiouxX%", fo[pos]))
				{
					pos = parsel2(f, pos, fo, ap);
					break ;
				}
				else if (!ft_strchr("cspdiouxX%", fo[pos]))
					pos = modifiers(fo, f, ap, pos);
				break ;
			}
		}
		pos++;
	}
	return (f->nprinted);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_struct	*tab;
	int			result;
	int			pos;

	pos = 0;
	tab = (t_struct*)malloc(sizeof(t_struct));
	tab = flag_init(tab);
	va_start(ap, format);
	result = pf_parse_format(format, ap, tab, pos);
	va_end(ap);
	free(tab);
	return (result);
}
