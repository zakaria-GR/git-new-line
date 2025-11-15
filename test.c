#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int countToNewLine(char *str)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t		i;

	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		str = malloc(1);
		{
			if (!str)
				return NULL;
			str[0] = '\0';
			return (str);
		}
	}
	if (len > (s_len - start))
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return ((char *)str);
}

int	findnline(char *s)
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

void freeLeftover(char *str)
{
	char *temp;
	temp = str;
	//str = ft_substr(str, y+1, i-y);
	free(temp);
	//return temp;
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	if (count != 0)
	{
		if (size > SIZE_MAX / count)
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

char *get_next_line(int fd)
{
	int				found;
	ssize_t			nb_read;
	char			buff[BUFFER_SIZE+1];
	char			*line;
	static char		*stash;
	char			*temp;
	char			*leftover;

	int i;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(1);
		stash[0] = '\0';
	}
	while (!findnline(stash))
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == 0)
			break;
		if (nb_read < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		if (nb_read > 0)
		{
			buff[nb_read] = '\0';
			temp = ft_strjoin(stash, buff);
			free(stash);
			stash = temp;
		}
	}
	found = findnline(stash);
	if (stash != NULL)
	{
		if (found)
		{
			int y = countToNewLine(stash);
			line = ft_substr(stash, 0, y+1);
			int i = ft_strlen(stash);
			leftover = ft_substr(stash, y+1, i - (y+1));
			free(stash);
			stash = leftover;
			return line;
		}
		else if (stash[0] != '\0')
		{
			i = ft_strlen(stash);
			line = ft_substr(stash, 0, i);
			free(stash);
			stash = NULL;
			return line;
		}
		else if (stash[0] == '\0' && nb_read == 0)
		{
			free(stash);
			stash = NULL;
			return NULL;
		}
	}
	return NULL;
}

int main()
{
	
	int fd = open("test.txt", O_RDONLY);
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	int i = 0;
	while (i < 8)
	{
		char *ptr = get_next_line(fd);
		if (ptr != NULL)
		{
			printf("%s", ptr);
		}
		i++;
		free(ptr);
	}
	close(fd);
}
