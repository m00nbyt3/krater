#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void	rewrite(FILE *toread, FILE *towrite);
void	getpos(char *fname, char *flist[12]);
size_t	getflen(FILE *file);
size_t	buflen(char *buf);
void	arrzero(char *flist[12]);

int	main(void)
{
	DIR				*d;
	struct dirent	*dir;
	FILE			*nf;
	FILE			*wh;
	char 			buf[200];
	char			*files[12];
	int				i;

	arrzero(files);
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
		getpos(buf, files);
	}
	i = -1;
	while(files[++i] && i < 12)
		rewrite(fopen(files[i], "r"), wh);
	closedir(d);
	return(0);
}

void	rewrite(FILE *toread, FILE *towrite)
{	
	char	*buf;
	size_t	fsize;

	fsize = getflen(toread) - 2;
	buf = malloc(fsize);
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

void	getpos(char *fname, char *flist[12])
{
	char buf[1];
	int pos;

	FILE *file = fopen(fname, "r");
	fread(buf, sizeof(buf), 1, file);
	pos = atoi(buf);
	flist[pos] = strdup(fname); 
	fclose(file);
}

void	arrzero(char *flist[12])
{
	int i = -1;

	while(++i < 12)
		flist[i] = 0;
}