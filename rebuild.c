#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void	rewrite(FILE *toread, FILE *towrite);
size_t	getflen(FILE *file);
size_t	buflen(char *buf);

int	main(void)
{
	DIR				*d;
	struct dirent	*dir;
	FILE			*nf;
	FILE			*wh;
	char 			buf[200];
	d = opendir("end");
	wh = fopen("end/white", "w");
	while((dir = readdir(d)))
	{
		if (!strncmp(dir->d_name, ".", 1) || \
			!strncmp(dir->d_name, "..", 2) || \
			!strncmp(dir->d_name, "white", 5))
			continue;
		snprintf(buf, sizeof(buf), "end/%s", dir->d_name);
		printf("READING: %s\n", buf);
		rewrite(fopen(buf, "r"), wh);
	}
	closedir(d);
	return(0);
}

void	rewrite(FILE *toread, FILE *towrite)
{	
	char	*buf;
	size_t	fsize;

	fsize = getflen(toread);
	buf = malloc(fsize - 40);
	fseek(toread, 2L, SEEK_SET);
	fread(buf, fsize, 1, toread);
	fwrite(buf, fsize, 1, towrite);
	free(buf);
	fclose(toread);
}

size_t	getflen(FILE *file)
{
	size_t	cnum;

	fseek(file, 0L, SEEK_END);
	cnum = ftell(file);
	rewind(file);
	return(cnum);
}
