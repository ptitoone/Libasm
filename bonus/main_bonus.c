#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include "../colors.h"

size_t	ft_strlen(char const *str);
int     ft_strcmp(char *s1, char *s2);
char    *ft_strcpy(char *dest, char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char    *ft_strdup(char *s1);

//// BONUS ////
typedef struct	s_list t_list;
struct	s_list {
	void	*data;
	t_list	*next;
};

int		ft_atoi_base(char *str, char *base);
int		ft_list_size(t_list *list);
void	ft_list_push_front(t_list **list, void *data);
///////////////

int test_strlen(char *str)
{
    static int c;
    if (ft_strlen(str) == strlen(str))
    {
        printf(GRN "[%i.OK] " reset, ++c);
        fflush(stdout);
        return (1);
    }
    printf(RED "[%i.KO :'( ] " reset, ++c);
    fflush(stdout);
    return (0);
}

int test_strcmp(char *s1, char *s2)
{
    static int c;

    if (ft_strcmp(s1, s2) == strcmp(s1, s2))
    {
        printf(GRN "[%i.OK] " reset, ++c);
        fflush(stdout);
        return (1);
    }
    printf(RED "[%i.KO :'( ] " reset, ++c);
    fflush(stdout);
    return (0);
}

int test_strcpy(char *dest, char *src)
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
    fflush(stdout);
    return (0);
}

int test_write(int fd, const void *buf, size_t count)
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
    fflush(stdout);
    return (0);
}

int test_read(int fd, char *buf, size_t count)
{
    static int  c;
    char        *error_asm;
    char        buf_rd[5];
    int         fd_rd;
    int         read_res;
    int         ft_read_res;

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
    fflush(stdout);
    close(fd_rd);
    return (0);
}

static int test_strdup(char *str)
{
    static int  c;
    char        *dup;

    dup = ft_strdup(str);
    if (!strcmp(dup, str))
    {
        printf(GRN "[%i.OK] " reset, ++c);
        free(dup);
        fflush(stdout);
        return (1);
    }
    printf(RED "[%i.KO :'( ] " reset, ++c);
    fflush(stdout);
    return (0);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list != NULL)
	{
		list->data = content;
		list->next = NULL;
	}
	else
		return (NULL);
	return (list);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst;

	lst = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

t_list	*make_list(int size)
{
	t_list *list;

	if (size <= 0)
		return (NULL);
	list = ft_lstnew("content");
	while (--size > 0)
		ft_lstadd_back(&list, ft_lstnew("addback"));
	return(list);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;
	while (lst)
	{
		tmp = lst->next;
		lst->data = NULL;
		free(lst);
		lst = tmp;
	}
	lst = NULL; // May be NULL, useless..
}

static int test_atoi_base(char *str, char *base, int res)
{
	static int	c;
	int			decimal;

	decimal = ft_atoi_base(str, base);
	if (res == decimal)
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		return (1);
	}
    printf(RED "[%i.KO :'( ] " reset, ++c);
	fflush(stdout);
	return (0);

}

static int	test_list_size(t_list *list, int res)
{

	static int	c;

	if (ft_list_size(list) == res)
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
		free_list(list);
		return (1);
	}
    printf(RED "[%i.KO :'( ] " reset, ++c);
	fflush(stdout);
	free_list(list);
	return (0);

}

int	test_list_push_front(t_list **list, void *data)
{
	static int	c;

	t_list **tmp = list;
	ft_list_push_front(list, data);
	if (!strcmp((*list)->data, data))
	{
		printf(GRN "[%i.OK] " reset, ++c);
		fflush(stdout);
/* 		while (*list != NULL)
 * 		{
 * 			printf("\n%s\n", (*list)->data);
 * 			*list = (*list)->next;
 * 		}
 */
		free_list(*tmp);
		return (1);
	}
    printf(RED "[%i.KO :'( ] " reset, ++c);
	fflush(stdout);
	free_list(*tmp);
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
	t_list *list;

	list = NULL;
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
        test_strcpy(cpy, "ses morts!");
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
        test_strdup("0123456789");
    if(waitt(0.10))
        test_strdup("gogogogo");
    if(waitt(0.10))
        test_strdup("");
    if(waitt(0.10))
        test_strdup("grrrrr irr\t");
    if(waitt(0.10))
        test_strdup("the qwick brown fox jumps over de lazy dog");
    puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_atoi_base ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_atoi_base("\n-01", "01", -1);
 	if(waitt(0.10))
 		test_atoi_base("", "01", 0);
	if(waitt(0.10))
 		test_atoi_base("1", "01-", 0);
	if(waitt(0.10))
		test_atoi_base("-FF", "0123456789ABCDEF", -255);
	if(waitt(0.10))
		test_atoi_base("+--+300FF", "0123456789ABCDEF", 196863);
	if(waitt(0.10))
		test_atoi_base("--", "", 0);
	if(waitt(0.10))
		test_atoi_base("", "casimir", 0);
	if(waitt(0.10))
		test_atoi_base("ihh", "calikush", 255);
	if(waitt(0.10))
		test_atoi_base("yy", "youhavemail", 0);
	if(waitt(0.10))
		test_atoi_base("    +++--+-dd", "IcOdewithWorD", -42);
	if(waitt(0.10))
		test_atoi_base("    +++--+dd", "IcOdewithWorD", 42);
	if(waitt(0.10))
		test_atoi_base(" X/   +++--+-wO", "IcOdewithWorD", 0);
	if(waitt(0.10))
		test_atoi_base("wOT", "IcOdewithWorD", 67);
	puts("\n\n");


	printf(BCYN ".-~-.-~-.-~ [ ft_list_size ] ~-.-~-.-~-." reset "\n\n");
	if(waitt(0.10))
		test_list_size(make_list(0), 0);
 	for (int x = 0; x < 10; x++)
	{
		if(waitt(0.10))
			test_list_size(make_list(x), x);
	}
	puts("\n\n");  


  	printf(BCYN ".-~-.-~-.-~ [ ft_list_push_front] ~-.-~-.-~-." reset "\n\n");
	for (int x = 1; x < 10; x++)
	{
		if (waitt(0.10))
		{	
			list = make_list(x);
			test_list_push_front(&list, "popo");
		}
	}
	puts("\n");  
	return (0);
}
