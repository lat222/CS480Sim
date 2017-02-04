#include "sim1.h"

int main(int argc, char** argv) {
	char ** str = mdstore("md.txt");
	printf("%s",str[0]);
}

char** mdstore(char* file_name) 
{
	char new_char;
	char buff[255];
	FILE *inFilePtr;
	//char** md = malloc(sizeof(char*),1);
	int ops = 0;
	int programs = 0;
	int buff_index = 0;
	char* end = " S(end)0.";
	inFilePtr = fopen(file_name, "r");
	while(fgetc(inFilePtr) != ';')
	{

	}
	while((new_char = fgetc(inFilePtr)) != EOF && strcmp(buff, end) != 0)
	{
		buff[buff_index++] = new_char; 
		char* m = " A(start)0";
		if (strcmp(buff, m) == 0)
		{
			programs++;
			empty(buff);
			//printf("\n----------------------\n");
		}
		else if (new_char == ';')
		{
			if (programs == 1)
			{
				ops++;
			}
			//printf("%s |", buff);
			empty(buff);
			buff_index = 0;

		}
	}
	printf("Programs: %d Ops: %d", programs, ops);
	//fclose(inFilePtr);

	//inFilePtr = fopen(file_name, "r");
	fseek(inFilePtr,0,SEEK_SET);
	int g = (ops-1)*programs;
	char ** md = (char**) malloc(g*sizeof(char*));
	printf("\n\nmd size: %d\n\n",sizeof(md));
	buff_index = 0;
	int index_x = 0;
	int index_y = 0;
	while((new_char = fgetc(inFilePtr)) != ';'){
		//printf("%c", new_char);
	}
	while((new_char = fgetc(inFilePtr)) != EOF)
	{
		if(new_char!='\n')
		{
			buff[buff_index] = new_char; 
			char* m = " A(start)0;";
			if (strcmp(buff, m) != 0 && new_char==';')
			{
				//printf("strlen of buff = %d", strlen(buff));
				md[index_x+index_y*(ops-1)] = malloc(strlen(buff)+1);
				strcpy(md[index_x+index_y*(ops-1)], buff);
				//printf("%s\n", buff);
				//printf("x: %d y: %d, x+y*ops-1: %d\n", index_x, index_y, index_x+index_y*(ops-1));
				index_x++;
				if(index_x==(ops-1)){
					index_y++;
					index_x=0;
					//printf("\n-----------------------------------\n");
				}
				empty(buff);
				buff_index=0;
				//printf("\n----------------------\n");
			}
			else if(strcmp(buff,m) == 0)
			{
				//printf("%s\n\n\n", buff);
				empty(buff);
				buff_index=0;
			}
		}
	}

	fclose(inFilePtr);
	index_x = 0;
	for(index_x = 0; index_x<sizeof(md); index_x++){
		printf("%s\n",md[index_x]);
	}
	return md;
}

int md_size(char* file_name, int array_length){
	char new_char;
	char buff[255];
	FILE *inFilePtr;
	//char** md = malloc(sizeof(char*),1);
	int ops = 0;
	int programs = 0;
	int buff_index = 0;
	char* end = " S(end)0.";
	inFilePtr = fopen(file_name, "r");
	while(fgetc(inFilePtr) != ';')
	{

	}
	while((new_char = fgetc(inFilePtr)) != EOF && strcmp(buff, end) != 0)
	{
		buff[buff_index++] = new_char; 
		char* m = " A(start)0";
		if (strcmp(buff, m) == 0)
		{
			programs++;
			empty(buff);
			//printf("\n----------------------\n");
		}
		else if (new_char == ';')
		{
			if (programs == 1)
			{
				ops++;
			}
			//printf("%s |", buff);
			empty(buff);
			buff_index = 0;

		}
	}
	printf("Programs: %d Ops: %d", programs, ops);
}

// empties out the buffer so that it can new ops can be held
void empty(char *var) {
    int i = 0;
    while(var[i] != '\0') {
        var[i] = '\0';
        i++;
    }
}
