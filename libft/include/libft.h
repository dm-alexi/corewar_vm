/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:14:21 by sscarecr          #+#    #+#             */
/*   Updated: 2020/03/15 22:31:09 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

typedef struct	s_s
{
	void		*content;
	size_t		content_size;
	struct s_s	*next;
}				t_list;

/*
				** libc functions
*/

void			*ft_memset(void *ptr, int val, size_t num);
void			ft_bzero(void *ptr, size_t num);
void			*ft_memcpy(void *dst, const void *src, size_t num);
void			*ft_memccpy(void *dst, const void *src, int val, size_t num);
void			*ft_memmove(void *dst, const void *src, size_t num);
void			*ft_memchr(const void *ptr, int val, size_t num);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t num);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strncat(char *dst, const char *src, size_t num);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *str, int val);
char			*ft_strrchr(const char *str, int val);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
int				ft_strcmp(const char *str1, const char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t num);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

/*
				** additional functions
*/

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned intstart, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
				** list processing functions
*/

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
				** other useful functions
*/

int				ft_isspace(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
long int		ft_strtol(const char *nptr, char **endptr, int base);
long int		ft_atol(const char *nptr);
void			*ft_realloc(void *ptr, size_t size, size_t new_size);
void			ft_memswap(void *a, void *b, size_t size);
void			ft_isort(void *base, size_t num, size_t size,
					int (*compar)(const void*, const void*));
void			ft_qsort(void *base, size_t num, size_t size,
					int (*compar)(const void*, const void*));
void			ft_lstadd_sorted(t_list **alst, t_list *new,
					int (*compar)(const void*, const void*));
void			ft_lstsort(t_list **alst,
					int (*compar)(const void*, const void*));
int				ft_isqrt(int nb);
char			*ft_lltoa(long long n, int base, int upcase);
char			*ft_ulltoa(unsigned long long n, int base, int upcase);
size_t			ft_wcslen(const wchar_t *wcs);
size_t			ft_word_count(char const *s, char c);
int				ft_abs(int n);

/*
				** projects
*/

int				get_next_line(const int fd, char **line);
int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *line, ...);

#endif
