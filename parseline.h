#define PARSELINE_BUFSIZE 128
#define PARSELINE_DELIMITER " \t\r\n\a"
char **project1_split_line(char *line)
{
	int bufsize = PARSELINE_BUFSIZE;
	int pos = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "project1: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(line, PARSELINE_DELIMITER);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
	
		if (pos >= bufsize)
		{
			bufsize += 128;
			tokens = realloc(tokens, bufsize * sizeof(char));
			if (!tokens)
			{
				fprintf(stderr, "project1: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		
		token = strtok(NULL, PARSELINE_DELIMITER);
	}
	tokens[pos] = NULL;
	return tokens;
}
