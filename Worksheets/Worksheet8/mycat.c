#include "apue.h"
#include <stdio.h>

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		fprintf(stderr, "Number of bytes read from stdin: %d\n", n);

	if (n < 0)
		err_sys("read error");

	exit(0);
}
