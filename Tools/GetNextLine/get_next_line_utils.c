/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:09:58 by aait-ham          #+#    #+#             */
/*   Updated: 2019/11/06 20:46:17 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char		*ft_strjoin(char *s1, char *s2)
// {
// 	int		l1;
// 	int		i;
// 	char	*p;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	l1 = ft_strlen(s1);
// 	i = 0;
// 	p = malloc(sizeof(char *) * (l1 + ft_strlen(s2)));
// 	if (p == 0)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		p[i] = s1[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (s2[i] != '\0')
// 	{
// 		p[i + l1] = s2[i];
// 		i++;
// 	}
// 	p[i + l1] = '\0';
// 	return (p);
// }


char		*search(int fd, char **rest, int *ret)
{
	char	*tmp;
	char	*ptr;

	ptr = malloc(BUFFER_SIZE + 1);
	while (ft_strchr(*rest, '\n') == NULL)
	{
		*ret = read(fd, ptr, BUFFER_SIZE);
		ptr[*ret] = '\0';
		tmp = ft_strjoin(*rest, ptr);
		free(*rest);
		*rest = ft_strdup(tmp);
		free(tmp);
		if (*ret == 0)
			break ;
	}
	free(ptr);
	return (*rest);
}

// size_t		ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

// char		*ft_strchr(const char *s, int c)
// {
// 	while (*s != (unsigned char)c)
// 	{
// 		if (!*s++)
// 			return (0);
// 	}
// 	return ((char *)s);
// }
