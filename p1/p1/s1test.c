#include "s1test.h"

int main(int argc, char* argv[]) 
{
	char** configData = store_config("config1.cnf");
	if(configData[0] != '\0')
	{
		int loopThroughArray = 0;
		while(configData[loopThroughArray] != '\0')
		{
			printf("%s\n", configData[loopThroughArray++]);
		}
		char** metadata = store_metadata(configData[1]);	// parse the metadata file
		if(metadata[0] != '\0')
		{
			loopThroughArray = 0;
			while(metadata[loopThroughArray] != '\0')
			{
				printf("%s\n", metadata[loopThroughArray++]);
			}
		}
		else
		{
			printf("ERROR: %s metadata is not recognized\n", metadata[1]);
		}
	}
	else
	{
		printf("Error in Configuration File: %s.", configData[1]);
	}
	return 0;
}

char** store_config(char* fileName){
	int noErrors = 1;
	int linesStored = 0;
	char *fileString = get_string_of_file(fileName);
	char **array = (char**) malloc(10*sizeof(char*));
	char* error = (char*) malloc(50*sizeof(char));
	char* token = strtok(fileString, "\n");
	token = strtok(NULL,"\n");
	while(linesStored < 9 && noErrors)
	{
		//printf("%s\n", token);
		char* dataAlone = token + move_pointer_to_config_data(token, ':') + 2;
		//printf("%s - ", dataAlone);
		switch(linesStored)
		{
			case 0:
				if((noErrors = check_string_is_int_in_range(dataAlone,0,10))==0)
				{
					error = "Version data is not a number";
				}
				else
				{
					dataAlone = cut_string_at_char(dataAlone,'.');
				}
				break;

			case 1:
				if((noErrors = check_metadata_file(dataAlone))==0)
				{
					error = "Metadata file could not be found";
				}
				break;

			case 2:
				if((noErrors = check_cpu_scheduling_code(dataAlone))==0)
				{
					error = "CPU Scheduling Code is not recognized";
				}
				else
				{
					if(strcmp(dataAlone,"NONE")==0)
					{
						dataAlone = cpuSchedulingCodeDefault;
					}
				}
				break;
			case 3:
				if((noErrors = check_string_is_int_in_range(dataAlone,0,100))==0)
				{
					error = "Quantum time is not recognized";
				}
				break;
			case 4:
				if((noErrors = check_string_is_int_in_range(dataAlone,0,1048576))==0)
				{
					error = "Memory available is not recognized";
				}
				break;
			case 5:
				if((noErrors = check_string_is_int_in_range(dataAlone,1,1000))==0)
				{
					error = "Memory available is not recognized";
				}
				break;
			case 6:
				if((noErrors = check_string_is_int_in_range(dataAlone,0,10000))==0)
				{
					error = "Memory available is not recognized";
				}
				break;
			case 7:
				if((noErrors = check_log_to(dataAlone))==0)
				{
					error = "Log to location is not recognized";
				}
				break;
			case 8:
				noErrors = check_log_file_path(dataAlone);
				break;
		}
		array[linesStored] = dataAlone;
		linesStored++;
		token = strtok(NULL,"\n");
	}
	if(noErrors)
	{
		array[linesStored] = '\0';
		return array;
	}
	else
	{
		array[0] = '\0';
		array[1] = error;
		return array;
	}
}

char** store_metadata(char* fileName){
	int processesStored = 0;
	char *fileString = get_string_of_file(fileName);
	int processes = count_char_in_string(fileString,';');
	char **array = put_metadata_in_array(fileString,processes);
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
		if (inString[charInString] == charToCount)
		{
			instancesOfChar++;
		}
		charInString++;
	}
	return instancesOfChar;
}

int move_pointer_to_config_data(char* inString, char charToMovePointerPast)
{
	int pointer = 0;
	while(inString[pointer] != charToMovePointerPast)
	{
		pointer++;
	}
	return pointer;
}

char* cut_string_at_char(char* inString, char charToCutOut)
{
	char* returnString  = (char*) malloc((strlen(inString)+1)*sizeof(char)); 
	int pointer = 0;
	while(inString[pointer] != charToCutOut)
	{
		returnString[pointer] = inString[pointer++];
	}
	returnString[pointer] = '\0';
	return returnString;
}
char* cut_string_after_char(char* inString, char charToCutOut)
{
	char* returnString  = (char*) malloc((strlen(inString)+1)*sizeof(char)); 
	int pointer = 0;
	while(inString[pointer] != charToCutOut)
	{
		returnString[pointer] = inString[pointer++];
	}
	returnString[pointer++] = charToCutOut;
	returnString[pointer] = '\0';
	return returnString;
}

int check_string_is_int_in_range(char* data, int lowerBound, int upperBound)
{
	int intData = atoi(data);
	// if string of data is not 0, but version is, the string
	// cannot be turned into an int
	if((strcmp(data,"0")!=0) && intData == 0){
		return 0;
	}
	else if(intData<lowerBound || intData>upperBound)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int check_metadata_file(char* metadataFilePath)
{
	return 1;
}

int check_cpu_scheduling_code(char* code)
{
	if(strcmp(code,"NONE")==0 || strcmp(code,"FCFS-N")==0 ||
		strcmp(code,"SJF-N")==0 || strcmp(code,"FCFS-P")==0 ||
		strcmp(code,"SRTF-P")==0 || strcmp(code,"RR-P")==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_log_to(char* abort)
{
	if(strcmp(abort,"Monitor")==0 || strcmp(abort,"File")==0 ||
		strcmp(abort,"Both")==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_log_file_path(char* fp)
{
	return 1;
}

char** put_metadata_in_array(char* inString, int totalProcesses)
{
	char** arrayToReturn = (char**) malloc((totalProcesses+1)*sizeof(char*));
	char* token;
	token = strtok(inString, "\n");
	token = strtok(NULL,"\n");
	int processesStored = 0;
	int noUnacceptableData  = 1;
	int programStartsAndEnds = 0;
	int processStartsAndEnds = 0;
	while (processesStored<totalProcesses && noUnacceptableData != 0)
	{
		token = strtok(NULL,";");
		if(count_char_in_string(token, '\n')>0)
		{
			char* noNewLine = token+2;
			noUnacceptableData += check_metadata_is_acceptable(noNewLine);
			arrayToReturn[processesStored++] = noNewLine;
		}
		else if(token[0] == ' ')
		{
			char* noLeadingBlankSpace = token + 1;
			noUnacceptableData += check_metadata_is_acceptable(noLeadingBlankSpace);
			arrayToReturn[processesStored++] = noLeadingBlankSpace;
		}
		else
		{
			noUnacceptableData += check_metadata_is_acceptable(token);
			arrayToReturn[processesStored++] = token;
		}
	}
	if(noUnacceptableData != 0)
	{
		arrayToReturn[processesStored++] = token + 1;
		token = strtok(NULL,".");
		arrayToReturn[processesStored++] = token + 1;
		arrayToReturn[processesStored] = '\0';
		return arrayToReturn;
	}
	else
	{
		arrayToReturn[0] = '\0';
		arrayToReturn[1] = token;
		return arrayToReturn;
	}

}

int check_metadata_is_acceptable(char* data){
	char* dataWithoutNumbers = cut_string_after_char(data,')');
	if(strcmp(dataWithoutNumbers,"I(hard drive)") == 0 || 
		strcmp(dataWithoutNumbers,"I(keyboard)") == 0 ||
		strcmp(dataWithoutNumbers,"O(hard drive)") == 0 ||
		strcmp(dataWithoutNumbers,"O(monitor)") == 0 ||
		strcmp(dataWithoutNumbers,"O(printer)") == 0 ||
		strcmp(dataWithoutNumbers,"P(run)") == 0 ||
		strcmp(dataWithoutNumbers,"M(allocate)") == 0 ||
		strcmp(dataWithoutNumbers,"M(access)") == 0 ||
		strcmp(dataWithoutNumbers,"A(start)")==0 ||
		strcmp(dataWithoutNumbers,"S(start)")==0 ||
		strcmp(dataWithoutNumbers,"A(end)")==0 ||
		strcmp(dataWithoutNumbers,"S(end)")==0) 
	{
		return 0;
	}
	else
	{
		// unacceptable value
		return -1;
	}
}

int check_process_start_and_end(char* data)
{
	char* dataWithoutNumbers = cut_string_after_char(data,')');
	if(strcmp(dataWithoutNumbers,"A(start)")==0)
	{
		// set value equal to check whether A(start) can happen
		return 1;
	}
	else if(strcmp(dataWithoutNumbers,"A(end)")==0)
	{
		// set value equal to check whether A(end) can happen
		return -1;
	}
	else
	{
		return 0;
	}
}

int check_program_start_and_end(char* data)
{
	char* dataWithoutNumbers = cut_string_after_char(data,')');
	if(strcmp(dataWithoutNumbers,"S(start)")==0)
	{
		// set value equal to check whether A(start) can happen
		return 1;
	}
	else if(strcmp(dataWithoutNumbers,"S(end)")==0)
	{
		// set value equal to check whether A(start) can happen
		return -1;
	}
	else
	{
		return 0;
	}
}
