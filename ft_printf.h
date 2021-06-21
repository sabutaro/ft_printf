/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:17:07 by sperrin           #+#    #+#             */
/*   Updated: 2020/08/09 13:01:33 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

# define ALLSYMBOLS "cspdiuxX%-0.*123456789"

typedef struct		s_struct
{
	int				nprinted;
	int				zero;
	int				minus;
	int				width;
	int				dot;
	int				up;
	int				len;
	int				i;
	int				star;
}					t_struct;

char				*ft_ptoa(long long unsigned p);
char				*ft_u_itoa(unsigned int n);
int					ft_printf(const char *format, ...);
int					ifint(t_struct *f, va_list ap);
int					ifchar (va_list ap, t_struct *f);
int					ifhex(va_list ap, t_struct *f);
int					ifpointeur(va_list ap, t_struct *f);
int					ifstring(va_list ap, t_struct *f);
int					ifudecint(va_list ap, t_struct*f);
int					ifpercent(t_struct *f);
int					dot(const char *format, int start, t_struct *f, va_list ap);
int					tlist(int c);
int					flist(int c);
void				flag_digit(char c, t_struct *f);
void				if_up_or_not(char c, t_struct *f);
void				flag_star(va_list ap, t_struct *f);
t_struct			*flag_init(t_struct *f);
void				flag_minus(t_struct *f);
void				flag_reinit(t_struct *f);

#endif
