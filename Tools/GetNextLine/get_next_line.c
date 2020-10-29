/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:09:49 by aait-ham          #+#    #+#             */
/*   Updated: 2019/11/07 15:08:43 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char		*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char			*p;
// 	unsigned int	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s) < start)
// 		len = 0;
// 	p = malloc(len + 1);
// 	if (p == NULL)
// 		return (0);
// 	while (len--)
// 	{
// 		p[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	p[i] = '\0';
// 	return (char *)(p);
// }

// char		*ft_strcpy(char *dest, char *src)
// {
// 	int i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char		*ft_strdup(char *src)
// {
// 	const char	*dest;
// 	int			size;

// 	size = 0;
// 	while (src[size] != '\0')
// 		size++;
// 	dest = malloc(sizeof(char) * (size + 1));
// 	if (dest == 0)
// 		return (NULL);
// 	ft_strcpy((char *)dest, (char *)src);
// 	return ((char *)dest);
// }

int			find(char **line, char **rest, int retn)
{
	int		len;
	char	*tmp;
	char	*ptr;

	if (retn == 1)
	{
		tmp = ft_strchr(*rest, '\n');
		len = tmp - *rest;
		*line = ft_substr(*rest, 0, len);
		ptr = ft_strdup(*rest + (len + 1));
		free(*rest);
		*rest = ft_strdup(ptr);
		free(ptr);
	}
	else
	{
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return (retn);
}

int			get_next_line(int fd, char **line)
{
	static char		*rest[255];
	int				ret;

	ret = 0;
	if (fd < 0 || line == NULL || read(fd, NULL, 0) != 0)
		return (-1);
	if (!rest[fd])
		rest[fd] = ft_strdup("");
	search(fd, &rest[fd], &ret);
	if (ft_strchr(rest[fd], '\n'))
		return (find(&line[0], &rest[fd], 1));
	else if (ret == 0)
		return (find(&line[0], &rest[fd], 0));
	return (0);
}
