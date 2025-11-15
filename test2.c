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
	ssize_t			nb_read;
	char			buff[BUFFER_SIZE+1];
	char			*temp;

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
			if(!temp)
				return (NULL);
			free(stash);
			stash = temp;
		}
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	int		i;
	int		y;
	int		start;
	char	*leftover;

	i = ft_strlen(stash);
	y = countToNewLine(stash) + 1;
	leftover = ft_calloc((i - y) + 1, 1);
	if (!leftover)
		return (NULL);
	start = 0;
	while (stash[0] != '\0')
	{
		leftover[start] = stash[y];
		start++;
		y++;
	}
	free(stash);
	stash = leftover;
	return (stash);
}
char *update_stash(char *stash)
{
	int		i;
	int		y;
	int		end;
	char	*leftover;

	i = ft_strlen(stash);
	y = countToNewLine(stash) + 1;
	leftover = ft_calloc((i - y) + 1, 1);
	if (!leftover)
		return (NULL);
	while (stash[0] != '\0')
	{
		leftover[y] = stash[i];
		y++;
		i++;
	}
	free(stash);
	stash = leftover;
	return (stash);
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
	stash = read_to_stash(fd, stash);
	leftover = stash;
	//
	
	found = findnline(stash);
	if (found)
	{
		temp = extract_line(stash);
		line = temp;
		free(stash);
		stash = update_stash(leftover);
		return line;
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
