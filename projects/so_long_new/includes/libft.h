/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:01:58 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/18 13:02:01 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

// LIBFT
int ft_atoi_base(const char *str, const char *base, size_t len_base);
int ft_atoi(const char *nptr);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_convert_base(
	const char *str, const char *base_from, const char *base_to);
void *ft_free_strs(char **strs, int size);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_ischarset(int c, const char *charset);
int ft_isdigit(int c);
int ft_islower(int c);
int ft_isprint(int c);
int ft_isspace(int c);
int ft_isupper(int c);
char *ft_itoa_base(int n, const char *base, size_t len_base);
char *ft_itoa(int n);
void ft_lstadd_back(t_list **alst, t_list *new);
void ft_lstadd_front(t_list **alst, t_list *new);
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstdelone(t_list *lst, void (*del)(void *));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list *ft_lstnew(void *content);
int ft_lstsize(t_list *lst);
void *ft_memccpy(void *dest, const void *src, int c, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int c, size_t n);
size_t ft_nbrlen(int n);
size_t ft_nbrlen_base(int n, size_t len_base);
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);
char **ft_split(char *s, char c);
char *ft_strcat(char *dest, const char *src);
char *ft_strchr(const char *s, int c);
size_t ft_strclen(const char *s, const char *charset);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dest, const char *src);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcat(char *dst, const char *src, size_t size);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlen(const char *s);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
int ft_strncmp(char *str1, char *str2, size_t n);
char *ft_strnstr(const char *big, const char *little, size_t len);
char *ft_strrchr(const char *s, int c);
char *ft_strsjoin(const char **strs, const char *sep);
char *ft_strtrim(char const *s1, char const *set);
char *ft_substr(char const *s, unsigned int start, size_t len);
int ft_toupper(int c);
int ft_tolower(int c);

// PRINTF
int ft_printf(const char *str, ...);
int search_str(const char *string, int searchedChar);
char *p_nbr(int nbr);
char *p_uint(unsigned int n, char format);
int p_char(char c);
int p_str(char *str, int *res_l);
int p_ptr(unsigned long long ptr);

// GNL
# define BUFFER_SIZE 42

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

char				*get_next_line(int fd, int *err);
t_gnl				*get_last(t_gnl *str);
void				create_line(t_gnl *str, char **line);
void				free_str(t_gnl *str);
int					is_newline(t_gnl *s);
int					ft_len(const char *str);
#endif
