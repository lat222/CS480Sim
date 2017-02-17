#include "s1test.h"

int main(int argc, char* argv[]) 
{
	char **metadata = mdstore("testfile.mdf");	// parse the metadata file
	int i = 0;
	while(metadata[i] != '\0')
	{
		printf("%s\n", metadata[i++]);
	}
	return 0;
}

char** mdstore(char* fileName){
	int processesStored = 0;
	char *fileString = get_string_of_file(fileName);
	//printf("%s\n\n", fileString);
	int processes = count_char_in_string(fileString,';');
	char **array = (char**) malloc((processes+1)*sizeof(char*));
	char* token;
	token = strtok(fileString, ":");
	token = strtok(NULL,";");
	while (processesStored<processes-1)
	{
		if(count_char_in_string(token, '\n')>0)
		{
			char* noNewLine = token+2;
			array[processesStored++] = noNewLine;
		}
		else
		{
			array[processesStored++] = token;
		}
		//printf("%s \n", token);
		token = strtok(NULL,";");
	}
	array[processesStored++] = token;
	//printf("%s \n", token);
	token = strtok(NULL,".");
	//printf("%s \n", token);
	array[processesStored++] = token;
	array[processesStored] = '\0';
	return array;
}

char* get_string_of_file(char* fileName)
{
	int fileSize;
	char *file;
	FILE *inFilePtr = fopen(fileName, "rb");
	fseek(inFilePtr, 0, SEEK_END);
	fileSize = ftell(inFilePtr);
	rewind(inFilePtr);
	file = malloc((fileSize + 1) * (sizeof(char)));
	fread(file, sizeof(char), fileSize, inFilePtr);
	fclose(inFilePtr);
	return file;
}

int count_char_in_string(char* inString, char charToCount)
{
	int instancesOfChar = 0;
	int charInString = 0;
	while(inString[charInString]!='\0')
	{
		//printf("%c",inString[charInString]);
		if (inString[charInString] == charToCount)
		{
			instancesOfChar++;
			//printf(" :)\n");
		}
		charInString++;
	}
	return instancesOfChar;
}
