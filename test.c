#include "get_next_line_bonus.h"

static count(char *str)
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
	while (s[i] == '\n')
		return 1;
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
	static int	y;
	static char	buff[BUFFER_SIZE];
	char		*line;
	static char	*leftover;

	if (leftover == NULL)
	{
		leftover = malloc(1);
			leftover[0] = '\0';
	}
	if (findnline(leftover))
	{
		while (leftover != '\n')
		{
			line[i] = leftover[i];
			i++;
		}
		return line;
	}
	read(fd, buff, BUFFER_SIZE);
	y = count(buff);
	line = ft_substr(buff, i, y);
	leftover = malloc(BUFFER_SIZE - y);
	i = 0;
	line = ft_strjoin(leftover, buff);
	return (line);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
}
