/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:28:03 by joushin           #+#    #+#             */
/*   Updated: 2023/01/21 14:51:18 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define SAME_STR 0
# define MALLOC_FAIL_MES "Memory allocate fail\n"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		print_char(va_list ap);
int		print_str(va_list ap);
int		print_persent(va_list ap);

int		print_unsigned_int(va_list ap);
int		print_hex_lower(va_list ap);
int		print_hex_upper(va_list ap);
int		print_addr(va_list ap);
int		print_dec_int(va_list ap);

char	*ft_lltoa(long long n);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_print_addr(void *addr);

int		eprint_char(va_list ap);
int		eprint_str(va_list ap);
int		eprint_persent(va_list ap);
void	error_handle(char *s);

int		eprint_unsigned_int(va_list ap);
int		eprint_hex_lower(va_list ap);
int		eprint_hex_upper(va_list ap);
int		eprint_addr(va_list ap);
int		eprint_dec_int(va_list ap);

int		ft_eputnbr_base(unsigned int nbr, char *base);
int		ft_eprint_addr(void *addr);

int		ft_printf(const char *args, ...);
int		ft_eprintf(const char *args, ...);

char	*ft__strjoin(char *s1, char *s2);
char	*ft__strdup(const char *s1);
size_t	ft__strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlen(const char *str);

char	*get_next_line(int fd);
#endif
