#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc, char*argv[]) {

	// If less than 2 parameters.
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}

	int prev = -1;
	int character = -1;
	unsigned int count = 1;

	for (int i=1;i<argc;++i) {
		// Open file in read mode.
		FILE* file_ptr = fopen(argv[i], "r");
		if (file_ptr == NULL) {
			fprintf(stdout, "wzip: cannot open file\n");
			exit(1);
		}

		// Read characters from file until end of file.
		while ((character = fgetc(file_ptr)) != EOF) {
			if (character == prev) {
				// If character is same as the previous one then increase 
				// the counter by one and move to read next character.
				count++;
				continue;
			}
			
			// If we had previous character but current is different then write previous character to file. 
			// Format is number of characters as integer and then character as char.
			if (prev >= 0) {
				fwrite(&count, sizeof(int), 1, stdout);
				fwrite(&prev, sizeof(char), 1, stdout);
			}

			// Set current character as previous character and set count to 1.
			prev = character;
			count = 1;
		}
	
		fclose(file_ptr);
	}
	
	// If we have previous defined then write it to file.
	if (prev >= 0) {
		fwrite(&count, sizeof(int), 1, stdout);
		fwrite(&prev, sizeof(char), 1, stdout);
	}

	return 0;
}
