/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:22:19 by niclee            #+#    #+#             */
/*   Updated: 2024/12/16 23:10:39 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!c || c <= 0 || !s || s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *) &s[i]);
	return (NULL);
}

// int	ft_strchr(const char *s, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!c || c <= 0 || !s || s == NULL)
// 		return (0) ;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return (1);
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return (1);
// 	return (0);
// }

static void	ft_strcpy(char *dest, const char *src, size_t *index)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	index;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	if (s1 && *s1 != '\0')
		len1 = ft_strlen(s1);
	if (s2 && *s2 != '\0')
		len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	if (s1 && s1[0] != '\0')
		ft_strcpy(result, s1, &index);
	if (s2 && s2[0] != '\0')
		ft_strcpy(result, s2, &index);
	result[index] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*dest;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
