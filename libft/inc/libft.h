/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:02:47 by pibouill          #+#    #+#             */
/*   Updated: 2024/10/25 11:25:40 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <fcntl.h>

// ft_printf
# ifdef __APPLE__
#  define PTR_NULL "0x0"
# else
#  define PTR_NULL "(nil)"
# endif

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_LIMIT
#  define FD_LIMIT 1024
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//	C TYPE
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

//	STRINGS
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

//	STRINGS - MEMORY
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);

//	STDLIB
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//	PUT
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *str);

//	ADDITIONAL
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);

//	LISTS
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_lst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// ADDITIONS
int		ft_digitcount(long nb, int base, int sign);
int		ft_printf(const char *format, ...);
int		ft_intlen(int nbr);
int		ft_atoi_base(const char *str, unsigned int base);
int		ft_str_arr_len(char **ar);
char	*get_next_line(int fd);
int		ft_wordcount(const char *s, char c);
int		ft_printf_fd(int fd, const char *format, ...);
char	*ft_strndup(const char *s, int n);
int		ft_puts(const char *s);

// HELPERS
int		putchar_len(int c);
int		putstr_len(char *str);
int		putptr_len(unsigned long long ptr, int ptr_prefix);
int		put_nbr_u_hex_len(long n, int base, int is_uppercase);
int		putchar_len_fd(int c, int fd);
int		putstr_len_fd(char *str, int fd);
int		putptr_len_fd(unsigned long long ptr, int ptr_prefix, int fd);
int		put_nbr_u_hex_len_fd(long n, int base, int is_uppercase, int fd);

#endif
