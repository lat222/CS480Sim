//These methods are modified versions of the code found at the website stackoverflow.com/questions/7856741/how-can-I-load-a-whole-file-into-a-string-in-c
//The code utilizing the strtok method is original, however


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//This method utilizes the file-access code from stack overflow with code designed with the strtok method that splits the file into seperate strings.
void delimitMD()
{
//accesses file and creates the char variable "file_contents" which is used in the delimiting process seen below
	char *file_contents;
long input_file_size;
FILE *input_file = fopen("testfile.mdf", "rb");
fseek(input_file, 0, SEEK_END);
input_file_size = ftell(input_file);
rewind(input_file);
file_contents = malloc((input_file_size + 1) * (sizeof(char)));
fread(file_contents, sizeof(char), input_file_size, input_file);
fclose(input_file);
file_contents[input_file_size] = 0;
char * tkn;
/*strtok breaks up a string (in this case its file_contents) based on each occurence of the provided symbols(:;). In the case of the metadata file, I chose to delimit based on the symbols ";" and ":" because 
it was what seperated each piece of individual information. This obviously does not work for the configuration file provided, so I used different parameter for that file's delimitation
*/
 tkn = strtok (file_contents," :;");
	
	
//The while loop delimits so long as there is another substring left in the file. Once it reaches a null point, the delimiter ends its process and the strings are added to the queue	
  while (tkn != NULL)
  {
	addInt(tkn);
    tkn = strtok (NULL, ".;:");

  }

	
}

//This is the delimiter for the configuration file. Its delimitation is based off of different symbols than the metadata file
void delimitConfig()
{
char *file_contents;
long input_file_size;
FILE *input_file = fopen("config1.cnf", "rb");
fseek(input_file, 0, SEEK_END);
input_file_size = ftell(input_file);
rewind(input_file);
file_contents = malloc((input_file_size + 1) * (sizeof(char)));
fread(file_contents, sizeof(char), input_file_size, input_file);
//printf("%s", file_contents);
//printf("in delimit config");
fclose(input_file);
file_contents[input_file_size] = 0;
char * tkn;

/*
This delimitation makes tokens (that are strings themselves).
I split up this file based on line breaks, as the strings themselves are items that we want to put in the queue, but just one line at a time.
*/
 tkn = strtok (file_contents,"'\n'");
	
  while (tkn != NULL)

  {

	//addInt(tkn);
    addInt(76);
    printf("%s ", tkn);
    tkn = strtok (NULL, "\n");

  }
}
