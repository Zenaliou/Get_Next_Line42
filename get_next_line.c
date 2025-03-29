/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:31:41 by niclee            #+#    #+#             */
/*   Updated: 2024/12/17 14:49:08 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *str, char *str2)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (NULL);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!*stash || !**stash)
		return (ft_free(*stash, NULL), NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	line = ft_strdup(*stash);
	if ((*stash)[i] == '\n')
	{
		line[i + 1] = '\0';
		tmp = ft_strdup(*stash + i + 1);
		if (!tmp)
			return (ft_free(*stash, NULL), NULL);
		ft_free(*stash, NULL);
		*stash = tmp;
	}
	else
		*stash = ft_free(*stash, NULL);
	return (line);
}

// static char	*read_and_stash(int fd,	char *stash)
// {
// 	char	*buffer;
// 	char	*tmp;
// 	ssize_t	bytes_read;

// 	tmp = NULL;
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 		return (ft_free(stash, NULL), NULL);
// 	bytes_read = 1;
// 	buffer[0] = '\0';
// 	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 			return (ft_free(buffer, stash), NULL);
// 		if (bytes_read == 0)
// 			break ;
// 		buffer[bytes_read] = '\0';
// 		if (!stash)
// 		{
// 			stash = malloc(BUFFER_SIZE + 1);
// 			if (!stash)
// 				return (ft_free(buffer, NULL), NULL);
// 			stash[0] = '\0';
// 		}
// 		tmp = ft_strjoin(stash, buffer);
// 		if (stash)
// 			ft_free(stash, NULL);
// 		stash = tmp;
// 		if (!stash)
// 			break ;
// 	}
// 	return (ft_free(buffer, NULL), stash);
// }

static char	*join_stash_and_buffer(char *stash, char *buffer)
{
	char	*tmp;

	if (!stash)
	{
		stash = malloc(BUFFER_SIZE + 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	tmp = ft_strjoin(stash, buffer);
	ft_free(stash, NULL);
	return (tmp);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(stash, NULL), NULL);
	buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buffer, stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = join_stash_and_buffer(stash, buffer);
		if (!stash)
			break ;
	}
	return (ft_free(buffer, NULL), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free(stash, NULL);
		return (NULL);
	}
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(&stash);
	if (!line && stash)
		stash = NULL;
	return (line);
}
