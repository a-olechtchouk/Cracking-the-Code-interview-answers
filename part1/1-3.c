#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 32

/*remove the duplicate characters in a string without using any additional buffer
 NOTE: One or two additional variables are fine. An extra copy of the array is not.
 FOLLOW UP
Write the test cases for this method. */

//CODE IS TESTED AND WORKS :)

/* My first ideas on how to solve this problem:
1. Go through the string and count the number of occurences of each letter (store this 
in an int array where the ascii value of the char is the index) - this takes O(n) time.

2. Iterate through the string starting from the end, for each char check if that char is a duplicate
by checking if the value in the ary at its index is greater than 1. This will take O(n).

3. If it is greater than one and the character to the right of it is the null term, 
remove the duplicate by setting it equal to the null term. 
Then decremenent the value by 1 for that char's index.

4. If it is greater than one and the character to the right of it is NOT the null term, keep swapping
until the offending duplicate char is to the left of the null term and do STEP 3. Worse case is if a char
close to the beginning is a duplicate, where we'd have to swap (n/2) times. I think for n chars we'd swap
at most n/2 for each so I think the time complexity for Step 4 is O(n * (n/2)) which is O(n^2).

5. Otherwise do nothing and continue until you reach the beginning.

Do swaps with pointers. 

Total complexity is (I think) O(n + n + n^2/2) which is O(n^2).
*/

//function that returns a pointer to the last char in the array that is not a null term
char *ptr_last_char (char *buf, char *ptr){
	int done = 1;
	while (done){
		if (*ptr == '\0'){
			ptr--;
		}
		else{
			done = 0;
		}
	}
	return ptr;
}

int main (int argc, char **argv){

	if (argc != 2){
		printf("%s\n", "Recieved improper amount of arguments. Program requires 1.");
		exit(1);
	}

	//array that stores the amount of occurences of each char, indexed by the char's ascii value
	unsigned int num_of_chars[256] = {0};

	//buffer for user input to ensure string is null term'ed
	char buf[MAX_LEN];
	strncpy(buf, argv[1], MAX_LEN-1);
	buf[MAX_LEN-1] = '\0';

	int str_len = strlen(buf);
	if (str_len == 1){
		printf("%s\n", buf);
		exit(0);
	}

	//index into the array based on the char's ascii value
	unsigned int char_index;

	int i = 0;
	for (i; i < str_len; i++){
		char_index = buf[i];
		//add 1 for the occurences of each char
		num_of_chars[char_index] += 1;
	}
	i = 0;

	//ptr to the last char in array that is not a null term
	char *backwards_ptr = &buf[MAX_LEN-2];
	backwards_ptr = ptr_last_char(buf, backwards_ptr);

	//ptr to the char that is one character to the right of backwards_ptr
	char *ptr_next; 

	//temp char used for swapping
	char temp_char;

	//ptr used for swapping (since I dont want to change backwards_ptr as that will keep going backwards)
	char *ptr_swapping;

	//iterate over all chars by moving backwards_ptr to the left 1 char.
	for (i; i < str_len; i++){

		char_index = *backwards_ptr;

		//check if char is a duplicate (if its occurence value is greater than 1)
		if (num_of_chars[char_index] > 1){

			ptr_swapping = backwards_ptr;
			ptr_next = backwards_ptr + 1;

			//check if duplicate char is not next to a null term, continue swapping until it is.
			while (*ptr_next != '\0'){

				temp_char = *ptr_swapping;
				*ptr_swapping = *ptr_next;
				*ptr_next = temp_char;

				//move pointers one char to the right. ptr_swapping is our original duplicate char.
				ptr_swapping++;
				ptr_next++;
			}
			
			//now the character to the right of the duplicate HAS to be the null term,
			//so we can remove the duplicate character and decrement the occurence value.
			*ptr_swapping = '\0';
			num_of_chars[char_index] -= 1;		
		}
		backwards_ptr--;
	}
	printf("%s\n", buf);
	exit(0);
}








