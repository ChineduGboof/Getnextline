/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cegbulef <cegbulef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:48:10 by cegbulef          #+#    #+#             */
/*   Updated: 2022/12/06 06:04:20 by cegbulef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*readfile(int fd, char *buf, char *allstr)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (0);
		else if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		if (!allstr)
			allstr = ft_strdup("");
		temp = allstr;
		allstr = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (allstr);
}

static char	*extract(char *str)
{
	size_t	i;
	char	*remains;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	remains = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*remains == '\0')
	{
		free(remains);
		remains = NULL;
	}
	str[i + 1] = '\0';
	return (remains);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*allstr[1024];
	size_t		intoverflow;

	intoverflow = (size_t)BUFFER_SIZE;
	if (fd < 0 || intoverflow <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (intoverflow + 1));
	if (!buf)
		return (NULL);
	line = readfile(fd, buf, allstr[fd]);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	allstr[fd] = extract(line);
	return (line);
}
