#define PROJECT1_BUFSIZE 1024

char *readline(void)
{
	int bufsize = 1024;
	int pos = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if(!buffer)//error checking: runs if buffer could not be initialized
	{
		fprintf(stderr, "project1: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	while (1)
	{
		c = getchar(); //reads characters
	
		if (c == EOF || c == '\n')//inputs null character if EOF is reached
		{
			buffer[pos] = '\0';
			return buffer;
		}
		else//inserts characters into buffer
		{
			buffer[pos] = c;
		}
		pos++
	
		if (pos >= bufsize) //reallocates the max buffer size if it is exceeded.
		{
			bufsize += 1024;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "project1: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
