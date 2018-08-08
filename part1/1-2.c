#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 32

//Reverse a string. Program takes 1 argument (a string). Uses two char pointers going forward and back.
int main (int argc, char **argv){

	if (argc != 2){
		printf("%s\n", "Recieved improper amount of arguments. Program requires 1.");
		exit(1);
	}

	char buf[MAX_LEN];
	strncpy(buf, argv[1], MAX_LEN-1);
	buf[MAX_LEN-1] = '\0';

	int str_len = strlen(buf);

	if (str_len == 1){
		printf("%s\n", buf);
		exit(0);
	}

	char *forwards = &buf[0];
	char *backwards = &buf[MAX_LEN-2];

	//find the last character in the string that is not a null term.
	//the backwards ptr will start at that index and move backwards.
	int done = 1;
	while (done){
		if (*backwards == '\0'){
			backwards--;
		}
		else{
			done = 0;
		}
	}

	//perform swapping and move ptrs forward and backward respectively.
	int num_swaps = str_len/2;

	char temp;

	int i=0;
	for (i; i < num_swaps; i++){
		//save a temp char so that one of the chars is saved for the swap
		temp = *forwards;

		//perform swap
		*forwards = *backwards;
		*backwards = temp;

		//move ptrs respectively
		forwards++;
		backwards--;
	}
	printf("%s\n", buf);
	exit(0);
}