#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*	Funcion that reads file line by line and sees if the line
	matches to given searchterm. If line matches to searchterm
	then line is printed for the user.
*/
static void process_stream(FILE* stream, const char* searchterm)
{
	while (feof(stream) == 0) {
		char* buffer = NULL;
		size_t buffer_size = 0;
		ssize_t line = getline(&buffer, &buffer_size, stream);
		if (line == -1) {
			free(buffer);
			if (errno != 0) {
				/* Failed to read line from file. */
				fprintf(stderr, "wcat: malloc failed\n");
				exit(1);
			}
			break;
		}
		
		if (strstr(buffer, searchterm) != NULL) {
			printf("%s", buffer);
		}
		free(buffer);
	}
	
	return;
}

int main(int argc, char*argv[]) {

	// If less than 2 parameters.
	if (argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		return 1;
	}

	char *searchterm = argv[1];

	if (argc == 2) {
		// If only searchterm parameter given then expect user to deliver text via stdin.
		process_stream(stdin, searchterm);
	}
	else {
		for (int i=2;i<argc;++i) {
			// Open file in read mode.
			FILE* file_ptr = fopen(argv[i], "r");
			if (file_ptr == NULL) {
				fprintf(stdout, "wgrep: cannot open file\n");
				exit(1);
			}

			process_stream(file_ptr, searchterm);
		
			fclose(file_ptr);
		}
	}
	
	return 0;
}
