#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc, char*argv[]) {

	// If less than 2 parameters given then show the usage message.
	if (argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		return 1;
	}

	for (int i=1;i<argc;++i) {
		// Open file in read mode.
		FILE* file_ptr = fopen(argv[i], "r");
		if (file_ptr == NULL) {
			fprintf(stdout, "wunzip: cannot open file\n");
			exit(1);
		}

		while (feof(file_ptr) == 0) {
			// Read integer from stream.
			int number_of_chars = 0;
			int read = fread(&number_of_chars, sizeof(int), 1, file_ptr);
			if (read == 0) {
				continue;
			}

			// Read character from stream.
			char ch;
			read = fread(&ch, sizeof(char), 1, file_ptr);
			if (read == 0) {
				continue;
			}

			// Print as many times the character as needed.
			for(int i=0;i<number_of_chars;++i) {
				fprintf(stdout, "%c", ch);
			}
		}

		fclose(file_ptr);
	}

	return 0;
}
