#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int index_of_newline(char *str)
{
	int i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	return i;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	has_newline(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return 1;
		i++;
	}
	return 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	y = 0;
	while (i < (s1_len + s2_len))
		s3[i++] = s2[y++];
	s3[i] = '\0';
	return (s3);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	if (count != 0)
	{
		if (count > SIZE_MAX / size)
		{
			return (NULL);
		}
	}
	temp = (unsigned char *)malloc(count * size);
	if (!temp)
	{
		return (NULL);
	}
	while (i < (count * size))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}

char *read_to_stash(int fd, char *stash)
{
    ssize_t nb_read;
    char    *buff;
    char    *temp;

    buff = malloc(BUFFER_SIZE + 1);
    if (!buff)
        {
            free(stash);
            return (NULL);
        }
    while (!has_newline(stash))
    {
        nb_read = read(fd, buff, BUFFER_SIZE);
        if (nb_read == 0)
            break;
        if (nb_read < 0)
        {
            free(stash);
            free(buff);
            return (NULL);
        }
        buff[nb_read] = '\0';
        temp = ft_strjoin(stash, buff);
        if (!temp)
        {
            free(buff);
            free(stash);
            return (NULL);
        }
        free(stash);
        stash = temp;
    }
    free(buff);
    return (stash);
}


char	*get_line_from_stash(char *stash)
{
    int	i, y, start;
    char	*line;

    if (!stash || stash[0] == '\0')
        return NULL;

    if (has_newline(stash))
    {
        y = index_of_newline(stash) + 1;
        line = ft_calloc(y + 1, 1);
        if (!line)
            return (NULL);
        start = 0;
        while (start < y)
        {
            line[start] = stash[start], 
            start++;
        }
        line[start] = '\0';
        return line;
    }
    i = ft_strlen(stash);
    line = ft_calloc(i + 1, 1);
    if (!line)
        return NULL;
    start = 0;
    while (start < i)
        line[start] = stash[start], start++;
    line[start] = '\0';
    return line;
}

char *trim_stash(char *stash)
{
    int start;
    int i;
    int len;
    char *leftover;

    if (!stash)
        return NULL;
    if (!has_newline(stash))
    {
        free(stash);
        return NULL;
    }
    len = ft_strlen(stash);
    start = index_of_newline(stash) + 1;
    leftover = ft_calloc(len - start + 1, 1);
    if (!leftover)
    {
        free(stash);
        return NULL;
    }
    i = 0;
    while (stash[start])
        leftover[i++] = stash[start++];
    free(stash);
    return leftover;
}

char *get_next_line(int fd)
{
	char			*line;
	static char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_to_stash(fd, stash);
	line = get_line_from_stash(stash);

	stash = trim_stash(stash);

	return line;
}

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
