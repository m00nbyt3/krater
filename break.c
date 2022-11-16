#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void	safe_exit(int fd);
void	devide(int fd, size_t cnum);
void	chkdir(char *name);
char	*rdstring(size_t f1, int f2, int f3);
int		getscs(size_t num);

int	main(void)
{
	int		fd;
	FILE 	*file;
	size_t	cnum;
	char	c;

	fd = open("prebinary/a.out", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR OPENING fd\n");
		exit(1);
	}
	cnum = 0;
	file = fdopen(fd, "r");
	fseek(file, 0L, SEEK_END);
	cnum = ftell(file);
	rewind(file);
	printf("CNUM: %zu\n", cnum);
	fclose(file);
	chkdir("end");
	devide(fd, cnum);
	safe_exit(fd);
}

void	devide(int fd, size_t cnum)
{
	FILE	*nf1;
	int		hex;
	char	buf[200];
	char	*nfname;
	int		scs;

	scs = getscs(cnum);
	hex = 0;
	while(hex < scs)
	{
		nfname = rdstring(cnum, fd, hex);
		snprintf(buf, sizeof(buf), "end/%s.m0", nfname);
		nf1 = fopen(buf, "w");
		fprintf(nf1, "%04x\n", hex);
		fclose(nf1);
		hex++;
	}
	fclose(nf1);
}

void	safe_exit(int fd)
{
	close(fd);
	printf("EXITED SAFELY\n");
	exit(0);
}

void	chkdir(char *name)
{
	char buf[100];
	if (!access(name, F_OK))
	{
		snprintf(buf, sizeof(buf), "rm -rf %s", name);
		system(buf);
	}
	snprintf(buf, sizeof(buf), "mkdir %s", name);
	system(buf);
}

char	*rdstring(size_t f1, int f2, int f3)
{
	int		r;
	int		i;
	char	*new;
	char	char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	srand((f1 + f2) * (f3 + f2 + 1) * (unsigned int)(time(NULL)));
	r = (rand() % (10 - 5 + 1)) + 5;
	new = malloc((r + 1) * sizeof(char));
	for(i = 0; i < r; i++)
		new[i] = char1[rand() % (sizeof char1 - 1)];
	new[i] = 0;
	return(new);
}

int		getscs(size_t num)
{
	int	i;

	i = 4;
	while(i <= 12)
	{
		if (num % i == 0)
			return(i);
		i++;
	}
	srand(num * (unsigned int)(time(NULL)));
	i = (rand() % (12 - 4 + 1)) + 4;
	return(i);
}