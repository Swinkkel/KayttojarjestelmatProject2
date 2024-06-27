#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char*argv[]) {

	// If less than 2 parameters.
	if (argc < 2) {
		return 0;
	}

	// Go through all parameters given.
	for (int i=1;i<argc;++i) {
		// Open file in read mode.
		FILE* file_ptr = fopen(argv[i], "r");
		if (file_ptr == NULL) {
			fprintf(stdout, "wcat: cannot open file\n");
			exit(1);
		}

		// Read and print lines from file in loop until end of file.
		while (feof(file_ptr) == 0) {
			char* buffer = NULL;
			size_t buffer_size = 0;
			ssize_t line = getline(&buffer, &buffer_size, file_ptr);
			if (line == -1) {
				free(buffer);
				if (errno != 0) {
					// Failed to read line from file.
					fprintf(stderr, "wcat: malloc failed\n");
					exit(1);
				}
				break;
			}

			printf("%s", buffer);
			free(buffer);
		}
		
		fclose(file_ptr);
	}
	
	return 0;
}
