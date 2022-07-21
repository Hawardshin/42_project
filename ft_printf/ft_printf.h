/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:01:09 by joushin           #+#    #+#             */
/*   Updated: 2022/07/21 14:31:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		print_dec_int(va_list ap);
int		print_char(va_list ap);
int		print_addr(va_list ap);
int		print_str(va_list ap);
int		print_unsigned_int(va_list ap);
int		print_hex_lower(va_list ap);
int		print_hex_upper(va_list ap);

char	*ft_lltoa(long long n);
int		print_persent(va_list ap);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_print_addr(void *addr);

#endif
