#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
//#include <semaphore.h>

int main() {
	FILE *in;
	char letter;
	
	// Open file
	in = fopen("test.txt", "r");
	
	// Check if file could be opened
	if ( in == NULL ) {
		perror("Error opening file");
		exit(1);
	}
	
	// Read characters
	while ( ( letter = fgetc(in) ) != EOF ) {
		printf( "%c", letter );
	}
	
	// Close file
	fclose(in);
	
	return 0;
}