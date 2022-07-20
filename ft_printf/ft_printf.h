/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:01:09 by joushin           #+#    #+#             */
/*   Updated: 2022/07/20 16:40:03 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>

int		print_dec_int(va_list ap);
int		print_char(va_list ap);
int		print_addr(va_list ap);
int		print_str(va_list ap);
int		print_unsigned_int(va_list ap);
int		print_hex_lower(va_list ap);
int		print_hex_upper(va_list ap);
char	*ft_lltoa(long long n);
int		print_persent(va_list ap);

#endif
