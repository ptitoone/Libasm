#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include "colors.h"

size_t	ft_strlen(char const *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(char *s1);

int	test_strlen(char *str)
{
	static int c;
	if (ft_strlen(str) == strlen(str))
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	return (0);
}

int	test_strcmp(char *s1, char *s2)
{
	static int c;

	if (ft_strcmp(s1, s2) == strcmp(s1, s2))
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	return (0);
}

int	test_strcpy(char *dest, char *src)
{
	static int c;
	char *cpy;

	cpy = ft_strcpy(dest, src);
	if (!strcmp(cpy, src))
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	return (0);
}

int	test_write(int fd, const void *buf, size_t count)
{
	static int c;
	char *error_asm;
	
	if ( write(fd, buf, count) == ft_write(fd, buf, count))
	{
		if (errno != 0)
		{
			error_asm = strerror(errno);
			write(fd, buf, count);
			if (strcmp(error_asm, strerror(errno)))
			{
				printf(RED "[%i. WRONG ERRNO] " reset, ++c);
				fflush(stdout);
				return (0);
			}
		}
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	return (0);
}

int	test_read(int fd, char *buf, size_t count)
{
	static int	c;
	char		*error_asm;
	char		buf_rd[5];
	int			fd_rd;
	int			read_res;
	int			ft_read_res;

	fd_rd = open("file.txt", O_RDONLY);
	read_res = read(fd_rd, buf_rd, count);
	ft_read_res = ft_read(fd, buf, count);
	if (ft_read_res < 0)
	{
		ft_read_res = read(fd, buf, count);
		if (ft_read_res < 0)
		{
			printf(GRN "[%i.OK] " reset, ++c);
			fflush(stdout);
			close(fd_rd);
			return (1);
		}
	}
	else if (read_res == ft_read_res)
	{
		if (errno != 0)
		{
			error_asm = strerror(errno);
			read(fd, buf, count);
			if (strcmp(error_asm, strerror(errno)))
			{
				printf(RED "[%i. WRONG ERRNO] " reset, ++c);
				fflush(stdout);
				return (0);
			}
		}
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		close(fd_rd);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	close(fd_rd);
	return (0);
}

static int test_strdup(char *str)
{
	static int	c;
	char		*dup;

	dup = ft_strdup(str);
	if (!strcmp(dup, str))
	{
		printf(GRN "[%i.OK] " reset, ++c);
		free(dup);
		fflush(stdout);
		return (1);
	}
	printf(RED "[%i.KO :'( ] " reset, ++c);
	return (0);
}

static int waitt(double sec)
{

	clock_t start, end = 0;
	double total = 0;

	start = clock();
	end = 0;
	while (total / CLOCKS_PER_SEC < sec)
	{
		end = clock();
		total = end - start;
	}
	return (1);
}

static void	print_header(char *path, char *color)
{
	int fd;
	char c[1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("%s", strerror(errno));
	puts(color);
	while(read(fd, &c, 1))
		write(1, c, 1);
	puts(reset);
	close(fd);
}

int main()
{
	char cpy[12];
	char buf[5];
	char tmp_file_name[] = "/tmp/tmp-XXXXXX";
	int fd_write;
	int fd_read;

	fd_write = mkstemp(tmp_file_name);
	fd_read = open("file.txt", O_RDONLY);
	unlink(tmp_file_name);
	print_header("header", YEL);
	waitt(1);

	printf(BCYN ".-~-.-~-.-~ [ ft_strlen ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_strlen("0123456789");
	if(waitt(0.10))
		test_strlen("The lenght of this string is???");
	if(waitt(0.10))
		test_strlen("BlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlablaBlabla");
	if(waitt(0.10))
		test_strlen("");
	if(waitt(0.10))
		test_strlen("*ùm***ù*$&é$*ç(-_à-(àà-à-");
	waitt(0.2);
	puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_strcmp ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_strcmp("0123456789", "0123456789");
	if(waitt(0.10))
		test_strcmp("4040gogogogo", "4041gogogogo");
	if(waitt(0.10))
		test_strcmp("kljsdlkfj", "");
	if(waitt(0.10))
		test_strcmp("", "sdfdsf");
	if(waitt(0.10))
		test_strcmp("lksdjfkljfmliofjqsdmlijfoidsqjf:liqsdjfmolqisdjflmiqdsjlifmjqvm", "lksdjfkljfmliofjqsdmlijfoidsqjf:liqsdjfmolqisdjflmiqdsjlifmjqvm");
	if(waitt(0.10))
		test_strcmp("", "");
	waitt(0.2);
	puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_strcpy ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_strcpy(cpy, "0123456789");
	if(waitt(0.10))
		test_strcpy(cpy, "gogogogo");
	if(waitt(0.10))
		test_strcpy(cpy, "soo moo!");
	if(waitt(0.10))
		test_strcpy(cpy, "");
	if(waitt(0.10))
		test_strcpy(cpy, "X");
	if(waitt(0.10))
		test_strcpy(cpy, "kjfdlgjdfkl");
	waitt(0.2);
	puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_write ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_write(fd_write, "hello", 1);
	if(waitt(0.10))
		test_write(fd_write, "hello", 2);
	if(waitt(0.10))
		test_write(fd_write, "hello", 3);
	if(waitt(0.10))
		test_write(fd_write, "hello", 4);
	if(waitt(0.10))
		test_write(fd_write, "hello", 5); 
	close(fd_write);
	if(waitt(0.10))
		test_write(fd_write, "hello", 6);
	waitt(0.2);
	puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_read ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_read(fd_read, buf, 1);
	if(waitt(0.10))
		test_read(fd_read, buf, 2);
	if(waitt(0.10))
		test_read(fd_read, buf, 3);
	if(waitt(0.10))
		test_read(fd_read, buf, 4);
	if(waitt(0.10))
		test_read(fd_read, buf, 5);
	if(waitt(0.10))
		test_read(fd_read, NULL, 6 - 1);
	close(fd_read);
	if(waitt(0.10))
		test_read(fd_read, buf, 7 - 2);
	if(waitt(0.10))
		test_read(fd_read, NULL,  8 - 3);
	waitt(0.2);
	puts("\n\n"); 
	
	
	printf(BCYN ".-~-.-~-.-~ [ ft_strdup ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_strdup("");
	if(waitt(0.10))
		test_strdup("0123456789");
	if(waitt(0.10))
		test_strdup("gogogogo");
	if(waitt(0.10))
		test_strdup("");
	if(waitt(0.10))
		test_strdup("grrrrr irr\t");
	if(waitt(0.10))
		test_strdup("the qwick brown fox jumps over de lazy dog");
	waitt(0.2);
	puts("\n\n");  

	return (0);
}
