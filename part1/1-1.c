#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256
#define NUM_BYTES 32

//checks a string for unique characters.

//returns 1 on failure (char is not unique), 0 on success (char is unique and bit is now set)
int check_and_set_bit (int char_val, unsigned char *bit_map){

	//since each unsigned char is 8 bits
	int bit_index = char_val / 8;

	//how many bits to shift
	int shift_index  = char_val % 8;

	//shift bit to proper place to prepare byte for AND (so we can check if the bit is already 1)
	unsigned char shifted_bit_in_byte = (128 >> shift_index);

	//AND the shifted_bit_in_byte with the corresponding byte in the bit_map
	unsigned char AND_result = (bit_map[bit_index] & shifted_bit_in_byte);

	//if the AND operation returns the same byte as shifted_bit_in_byte, then there must have been a 1
	//already in that place, thus the char is NOT unique. thus return 1 for failure.
	if (shifted_bit_in_byte == AND_result){
		return 1;
	}

	//otherwise, set the bit and return 0
	bit_map[bit_index] |= shifted_bit_in_byte;
	return 0; 


}



//prints and exits with 1 on failure (string is not unique), 0 on success (each char is unique)
int main (int argc, char **argv){

	if (argc != 2){
		printf("%s\n", "Recieved improper amount of arguments. Program requires 1.");
		exit(1);
	}

	//allocate 32 bytes (256 bits for each ascii character) for the string
	char buf[32];

	//move the user-inputed string into the buffer
	strncpy(buf, argv[1], MAX_LEN-1);

	//null-terminate the buffer
	buf[MAX_LEN-1] = '\0';

	//create bitmap for each character
	unsigned char bit_map[NUM_BYTES];

	//initialize bit_map to all 0's
	memset(bit_map, 0, NUM_BYTES);

	//get size of string in buf
	int str_size = strlen(buf);

	int i = 0;
	for (i; i < str_size; i++){
		int char_in_str = buf[i];
		if (check_and_set_bit(char_in_str, bit_map) == 1){
			printf("%d\n", 1);
			exit(1);
		}
	}

	printf("%d\n", 0);
	exit(0);

}





