#include "sim1.h"

int main(int argc, char** argv) {
	MD  inmd = mdstore("testfile.mdf");	// parse the metadata file
	read_md(inmd);// print the struct containing the metadata file
	CFG inconfig = configStore("config1.cnf");	// parse the config file
	read_config(inconfig);	// print struct containg the config file
	return 0;
}

/*This method parses the metadata file
It takes in a string of the file name and returns a struct with the files programs*/
MD mdstore(char* file_name) 
{
	MD md;			// initialize the struct that will store the file contents
	FILE *inFilePtr;	// make pointer for file name
	char new_char;	// this char is for reading in chars from the file
	char buff[255];	//this is a buffer that will hold all of the ops in the file
	char program_string[255]; // this buffer will hold each of the programs in the file; so A(start)0 to A(end)0
	int program_ind, buff_index, programs = 0;	// all of these represent some kind of index
	char* end = " S(end)0.";	// the last op of the metadata file
	// open the file for reading
	inFilePtr = fopen(file_name, "r");
	// check that the file was opened
	if (inFilePtr == NULL) {
        perror("FILE OPEN ERROR: ");
    }
    // read all the way to the first semi-colon
    // helps to keep the buff[] from being filed with useless chars
	while(fgetc(inFilePtr) != ';')
	{

	}
	// loop through all chars in the file
	// but stop looping if you get to the End of File (EOF)
	// or if you get to the last op of the file
	while((new_char = fgetc(inFilePtr)) != EOF && strcmp(buff, end) != 0)
	{
		buff[buff_index++] = new_char; // add the char to the buffer
		program_string[program_ind++] = new_char; // add it also to the program_string
		char* m = " A(end)0;"; // the last op of a program
		// if the buff or op is the last one of a program, store it in the md struct
		if (strcmp(buff, m) == 0)
		{
			// the struct only allows for 11 programs, no programs after that will be stored
			switch(programs){
				// stores programs up to 200 chars long, all other chars are cut off
				case 1:
					strncpy(md.ps1, program_string,200);
					break;
				case 2:
					strncpy(md.ps2, program_string,200);
					break;
				case 3:
					strncpy(md.ps3, program_string,200);
					break;
				case 4:
					strncpy(md.ps4, program_string,200);
					break;
				case 5:
					strncpy(md.ps5, program_string,200);
					break;
				case 6:
					strncpy(md.ps6, program_string,200);
					break;
				case 7:
					strncpy(md.ps7, program_string,200);
					break;
				case 8:
					strncpy(md.ps8, program_string,200);
					break;
				case 9:
					strncpy(md.ps9, program_string,200);
					break;
				case 10:
					strncpy(md.ps10, program_string,200);
					break;
				case 11:
					strncpy(md.ps11, program_string,200);
					break;
				case 12:
					strncpy(md.ps12, program_string,200);
					break;
			}
			programs++;	// add to the program index because another program was added
			//then empty all buffers, set their indices to 0 to begin reading in more
			empty(program_string);
			program_ind = 0;
			empty(buff);
			buff_index = 0;
		}
		// empties ops from buff in order to check only for ending ops
		else if (new_char == ';')
		{
			empty(buff);
			buff_index = 0;
		}
		//printf("%s\n", new_char);
	}
	// close the file and return the struct
	fclose(inFilePtr);
	return md;
}

// this file takes in the metadata struct and prints its information
void read_md(MD metad)
{
	// uses a while loop and switch statement to read through all of the
	// stored metadata file's information
	int index = 1;
	printf("The metadata file held the following information: \n");
	while (index < 13){
		switch(index){
			case 1:
				if(metad.ps1 != NULL){printf("%s, ",metad.ps1);}
			case 2:
				if(metad.ps2 != NULL){printf("%s, ", metad.ps2);}
			case 3:
				if(metad.ps3 != NULL){printf("%s, ",metad.ps3);}
			case 4:
				if(metad.ps4 != NULL){printf("%s, ",metad.ps4);}
			case 5:
				if(metad.ps5 != NULL){printf("%s, ",metad.ps5);}
			case 6:
				if(metad.ps6 != NULL){printf("%s, ",metad.ps6);}
			case 7:
				if(metad.ps7 != NULL){printf("%s, ",metad.ps7);}
			case 8:
				if(metad.ps8 != NULL){printf("%s, ",metad.ps8);}
			case 9:
				if(metad.ps9 != NULL){printf("%s, ",metad.ps9);}
			case 10:
				if(metad.ps10 != NULL){printf("%s, ",metad.ps10);}
			case 11:
				if(metad.ps11 != NULL){printf("%s, ",metad.ps11);}
			case 12:
				if(metad.ps12 != NULL){printf("%s",metad.ps12);}
		}
		index++;

	}
}

/* Similar to the above function, this one parses the config file.
	It takes in a String for the config file and returns a struct with its data*/
CFG configStore(char* file_name)
{
	FILE *inFilePtr;	// intialize the variable for the file
	char line[255];		// initialize a buffer for the data that must be stored
	CFG config_data;	// initialize the struct that will be returned
	char new_char;		// this char will store all read in chars
	int index, line_num = 0;	// indices for the buffer and to keep track of what line is being read
	// open the file
	inFilePtr = fopen(file_name, "r");
	// check if the file is null
	if (inFilePtr == NULL){
		perror("File open error: ");
	}
	// loop through all the characters in the file
	// if the character being read in is the end of file char, stop looping
	while((new_char = fgetc(inFilePtr)) != EOF){
		// add the character to the buffer
		line[index++] = new_char;
		// the part of the string before the colon is unecessary; so get rid of it
		if(new_char == ':')
		{
			index = 0;
			empty(line);
		}
		// check if we have reached the end of a line
		// the first end of line does not matter because it contains no information
		// those in between that one and the ninth do because they contain information
		// any lines thereafter will just be deleted
		else if(new_char == '\n')
		{
			if(line_num > 0 && line_num < 9)
			{
				printf("%d: %s \n", line_num, line);
				switch(line_num){
					case 1:
						strncpy(config_data.file_path, line,31);
						break;
					case 2:
						strncpy(config_data.cpu_scheduling, line,31);
						break;
					case 3:
						strncpy(config_data.quant_cyc, line,31);
						break;
					case 4:
						strncpy(config_data.mem_kb, line,31);
						break;
					case 5:
						strncpy(config_data.process_cyc, line, 31);
						break;
					case 6:
						strncpy(config_data.io, line,31);
						break;
					case 7:
						strncpy(config_data.log_to, line,31);
						break;
					case 8:
						strncpy(config_data.log_fp, line, 31);
						break;
				}
			}
			line_num++;
			empty(line);
			index = 0;
		}
	}
	return config_data;	// return the struct
}

// this file takes in the config struct and prints its information
void read_config(CFG config_data)
{
	// uses a while loop and switch statement to read through all of the
	// stored config file's information
	int index = 1;
	printf("The config file held the following information: \n");
	while (index < 9){
		switch(index){
			case 1:
				//strcpy (config_data.file_path, "hello");
				printf("%s, ",config_data.file_path);
			case 2:
				printf("%s, ", config_data.cpu_scheduling);
			case 3:
				printf("%s, ",config_data.quant_cyc);
			case 4:
				printf("%s, ",config_data.mem_kb);
			case 5:
				printf("%s, ",config_data.process_cyc);
			case 6:
				printf("%s, ",config_data.io);
			case 7:
				printf("%s, ",config_data.log_to);
			case 8:
				printf("%s",config_data.log_fp);
		}
		index++;

	}
}

// empties out the buffer so that it can new chars can be held
void empty(char* var) {
    int i = 0;
    while(var[i] != '\0') {
        var[i] = '\0';
        i++;
    }
}
