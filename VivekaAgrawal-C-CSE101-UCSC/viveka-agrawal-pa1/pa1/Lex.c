/*----------------------------------------------------------------------------
   Viveka Agrawal
   cruzID: viagrawa
   pa1
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 300

int main(int argc, char * argv[]) {
   char temp; // variable to store characters from infile
   int count = 0; // counter for number of lines in the infile
   int tokencount = 0; // counter for number of tokens
   int i = 0; // iterator for array of strings
   FILE *in; 
   FILE *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;

   // Checking the command line to see if user entered the correct number of arguments (3)
   if (argc != 3) {
	   printf("Usage: %s <input file> <output file>\n", argv[0]);
   	   exit(EXIT_FAILURE);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if (in == NULL) {
	   printf("Unable to open file %s for reading. \n", argv[1]);
	   exit(EXIT_FAILURE);
   }
   
   if(out == NULL) {
	   printf("Unable to open file %s for writing. \n", argv[2]);
	   exit(EXIT_FAILURE);
   }

   // counting the number of lines in the file
   for (temp = getc(in); temp != EOF; temp = getc(in)) {
	   if (temp == '\n') {
		count++;
     	   }
   }

   // create an array of strings to store the lines from the infile
   char arrayOfString[count][MAX_LEN];

   // open the file again to read the lines
   in = fopen(argv[1], "r");
   if (in == NULL) {
	   printf("Unable to open file %s for reading. \n", argv[1]);
      	   exit(EXIT_FAILURE);
   }

   // read each line of the input file, then count and print string tokens
   while (fgets(line, MAX_LEN, in) != NULL) {
	   token = strtok(line, " \n");
	   tokenlist[0] = '\0';
    	    
	   while(token != NULL) {
		   strcat(tokenlist, "   ");
		   strcat(tokenlist, token);
		   tokencount++;
         	   token = strtok(NULL, " \n");
      	   }
	   strcpy(arrayOfString[i], tokenlist);
	   i++;
   }

   // create a List whose elements are the indices of the above string array
   // these indices should be arranged in an order that indirectly sorts the array

   List indicesList = newList(); // creating an indices list
   for (int i = 0; i < count; i++) { // set i to 0 again to reuse it and iterate through
	   if (length(indicesList) == 0) {
		   // If indicesList is an empty list, append the first index into it -- there's no need to compare
		   append(indicesList, i);
	   }
	   else {
		   moveFront(indicesList); // Move to the front of the List storing the indices
		   int repeat = 1;
		   while (repeat == 1) {
			   int result = strcmp(arrayOfString[get(indicesList)], arrayOfString[i]);
			   // if the string pointed by the index stored in the indecList is lexographically 
			   // greater than or the same as the current string in the array
			   // then insert the index of the string from the array in the indicesList
			   // before the current index 
			   if (result >= 0) {
				   insertBefore(indicesList, i);
				   repeat = 0;
			   }
			   else {
				   int ind = index(indicesList);
				   if (ind == length(indicesList) - 1) {
					   append(indicesList, i);
					   repeat = 0;
				   }
				   else {
					   repeat = 1;
					   moveNext(indicesList); // move to the next index in the indicesList
				   }
			   }
		   }
	   }
   }

    // output the strings pointed to by the sorted indicesList to the outfile
    moveFront(indicesList);
    for (int i = 0; i < length(indicesList); i++) {
	    int indOfString = get(indicesList);
	    fprintf(out, "%s\n",arrayOfString[indOfString]);
	    moveNext(indicesList);
    }

    freeList(&indicesList);

    // close open files
    fclose(in);
    fclose(out);

    return(0);
}

