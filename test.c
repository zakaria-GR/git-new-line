#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static countToNewLine(char *str)
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

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc((s1_len + s2_len + 1) * sizeof(char));
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


char *get_next_line(int fd)
{
	int			i;
	int			y;
	static char	buff[BUFFER_SIZE];
	char		*line;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);

	if (leftover == NULL)
	{
		leftover = malloc(1);
			leftover[0] = '\0';
	}
	while (findnline(leftover))
	{
		y = countToNewLine(leftover);
		line = ft_substr(leftover, 0, y+1);
		i = ft_strlen(leftover);
		leftover = ft_substr(leftover, y+1, i);
		return line;
	}
	while (!findnline(leftover))
	{
		int z = read(fd, buff, BUFFER_SIZE);
		if (z == 0 && leftover[0] == '\0')
			return NULL;
		leftover = ft_strjoin(leftover, buff);
		if (findnline(leftover))
		{
			y = countToNewLine(leftover);//count until \n and stops before it
			line = ft_substr(leftover, 0, y+1);
			i = ft_strlen(leftover);
			leftover = ft_substr(leftover, y+1, i);
			return (line);
		}
		if (z == 0 && !findnline(leftover))
		{
			y = ft_strlen(leftover);
			line = ft_substr(leftover, 0, y);
			return (line);
		}
	}
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	int i=0;
	while (i<4)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
}
