#include "sim02.h"

int main(int argc, char* argv[]) 
{
	char** configData = store_config("config1.cnf"); 	// store config data in an array of char* or strings
	// check the array data
	// if the first item in the array IS NOT the '\0' character
	// everything in the config file was accepted
	if(configData[0] != '\0')
	{
		char** metadata = store_metadata(configData[1]);	// store metadata file in an array of char* or strings
		// if the first item in the array IS NOT the '\0' character
		// everything in the metadata file is acceptable
		if(metadata[0] != '\0')
		{	
			sim02(configData,metadata);

		}
		// prints what was unaccepted in the metadata file
		else
		{
			printf("%s.\n", metadata[1]);
		}
	}
	// prints what was unaccepted in the confiugration file
	else
	{
		printf("ERROR: %s.\n", configData[1]);
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
	int commands = count_char_in_string(fileString,';');
	char **array = put_metadata_in_array(fileString,commands);
	return array;
}

char* get_string_of_file(char* fileName)
{
	int fileSize;
	char *file;
	FILE *inFilePtr = fopen(fileName, "r");
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

// taken from http://stackoverflow.com/questions/8465006/how-to-concatenate-2-strings-in-c
char* concat(char *s1, char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1+len2+1);
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
    return result;
}

char* get_string_after_char(char* inString, char charToCutOut)
{
	char* returnString  = (char*) malloc((strlen(inString)+1)*sizeof(char)); 
	int inStringPointer = 0;
	int pointer = 0;
	while(inString[inStringPointer] != charToCutOut)
	{
		inStringPointer++;
	}
	inStringPointer++;
	while(inString[inStringPointer] != '\0')
	{
		returnString[pointer++] = inString[inStringPointer++];
	}
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

char** put_metadata_in_array(char* inString, int totalCommands)
{
	char** arrayToReturn = (char**) malloc((totalCommands+1)*sizeof(char*));
	char* token;
	token = strtok(inString, "\n");
	token = strtok(NULL,"\n");
	int processesStored = 0;
	int noUnacceptableData  = 1;
	int programStartsAndEnds = 0;
	int processStartsAndEnds = 0;
	while (processesStored<totalCommands && noUnacceptableData != 0 && programStartsAndEnds < 2 && programStartsAndEnds > -1
	  && processStartsAndEnds < 2 && processStartsAndEnds >-1)
	{
		token = strtok(NULL,";");	//Weird problem, strtok seems to save the next string and places it in the array, but changes it back later. Indices 1 and 0 though are identical.
		if(count_char_in_string(token, '\n')>0)
		{
			char* noNewLine = token+2;
			noUnacceptableData += check_metadata_is_acceptable(noNewLine);
			programStartsAndEnds += check_program_start_and_end(noNewLine);
			processStartsAndEnds += check_process_start_and_end(noNewLine);
			arrayToReturn[processesStored++] = noNewLine;
		}
		else if(token[0] == ' ')
		{
			char* noLeadingBlankSpace = token + 1;
			noUnacceptableData += check_metadata_is_acceptable(noLeadingBlankSpace);
			programStartsAndEnds += check_program_start_and_end(noLeadingBlankSpace);
			processStartsAndEnds += check_process_start_and_end(noLeadingBlankSpace);
			arrayToReturn[processesStored++] = noLeadingBlankSpace;
		}
		else
		{
			//noUnacceptableData += check_metadata_is_acceptable(token);
			programStartsAndEnds += check_program_start_and_end(token);
			//processStartsAndEnds += check_process_start_and_end(token);
			arrayToReturn[processesStored++] = token;
		}
	}
	if (noUnacceptableData == 0)
	{
		arrayToReturn[0] = '\0';
		arrayToReturn[1] = concat("Could not recognize metadata command ", token);
	}
	else if(processStartsAndEnds != 0){
		arrayToReturn[0] = '\0';
		if(processStartsAndEnds > 0)
		{
			arrayToReturn[1] = "ERROR: Missing A(end)0 for a process";
		}
		else
		{
			arrayToReturn[1] = "ERROR: Missing A(start)0 for a process";
		}
	}
	else if(programStartsAndEnds != 1){
		arrayToReturn[0] = '\0';
		if(programStartsAndEnds  > 1) {
			arrayToReturn[1] = "ERROR: Too many S(start)0 commands";
		}
		else {
			arrayToReturn[1] = "ERROR: Too many S(end)0 commands";
		}
	}
	else
	{
		token = strtok(NULL,".");
		char* noLeadingBlankSpace = token + 1;
		programStartsAndEnds += check_program_start_and_end(noLeadingBlankSpace);
		if(programStartsAndEnds == 0)
		{
			arrayToReturn[processesStored++] = noLeadingBlankSpace;
			arrayToReturn[processesStored] = '\0';
		}
		else
		{
			arrayToReturn[0] = '\0';
			arrayToReturn[1] = "ERROR: Missing the closing program command";
		}
	}
	return arrayToReturn;
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


void sim02(char** storedConfigData, char** inMetadata)
{
	clock_t difference;
	char holdStartString[1000];
	char *str = holdStartString;
	char holdRunString[10000];
	char *str1  = holdRunString;
	char** simLog = (char**) malloc(logStringLength*sizeof(char*));
	int logIndex = 0;
	simLog[logIndex++]="Operating System Simulator\n==========================\n\n\n";
	simLog[logIndex++]="Loaded configuration file\nLoaded meta-data file\n==========================\n\n\n"; 
	simLog[logIndex++]="Begin Simulation\n";
	clock_t start = clock();
	str += sprintf(str, "Time: %3d.%03d, System start\n", start/CLOCKS_PER_SEC, start*1000%1000/CLOCKS_PER_SEC);
	difference = clock()-start;
	str += sprintf(str, "Time: %3d.%03d, OS: Begin PCB Creation\n", difference/CLOCKS_PER_SEC,((difference*1000)/CLOCKS_PER_SEC%1000));
	
	// Store all processes and their PCBs here
	// Need access to both Processes list and PCB list
	// the process and its pcb are held on the same index within their respective lists

	int* processesIndices = divide_processes_by_index(inMetadata);
	int loopThroughProcesses = 0;
	int numberOfProcesses = get_num_processes(inMetadata);
	int* pcbStore = (int*) malloc((numberOfProcesses+1)*sizeof(int));
	char*** processesStore = (char***) malloc((numberOfProcesses+1)*sizeof(char**));
	while(loopThroughProcesses < numberOfProcesses)
	{
		//printf("\n\n((P%d))",loopThroughProcesses);
		if(loopThroughProcesses==0)
		{
			processesStore[loopThroughProcesses] = get_process_from_metadata(inMetadata,1,processesIndices[0]);
			pcbStore[loopThroughProcesses++] = 0;
		}
		else
		{
			processesStore[loopThroughProcesses] = get_process_from_metadata(inMetadata,
				processesIndices[loopThroughProcesses-1]+1,processesIndices[loopThroughProcesses]);
			pcbStore[loopThroughProcesses++] = 0;
		}
	}

	difference = clock()-start;
	str += sprintf(str, "Time: %3d.%03d, OS: All processes initialized in New state\n", difference/CLOCKS_PER_SEC,((difference*1000)/CLOCKS_PER_SEC%1000));
	
	set_pcbs_ready(pcbStore,numberOfProcesses); //sets all PCBs to ready;
	
	difference = clock()-start;
	str += sprintf(str, "Time: %3d.%03d, OS: All processes now set in Ready state\n", difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000);
	simLog[logIndex++] = holdStartString;

	// run all processes and sets PCBs to exit
	loopThroughProcesses = 0;
	while(loopThroughProcesses < numberOfProcesses)
	{
		int PCBstate = pcbStore[loopThroughProcesses];
		// Only run processes in ready state, which is int 1
		if (PCBstate == 1)
		 {
		 	PCBstate = 2; //Running state is int 2
		 	//printf(" ((P%d))\n",loopThroughProcesses);
			char** process = processesStore[loopThroughProcesses++];
			int loopThroughCommands = 0;
			char* command = process[loopThroughCommands];
			while(command != '\0')
			{
				if(strcmp(command,"A(start)0")==0)
				{
					difference = clock()-start;
					str1 += sprintf(str1,"Time: %3d.%03d, OS: Process %d set in Running State\n",difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000,
						loopThroughProcesses-1);
					command = process[loopThroughCommands++];
				}
				else if(strcmp(command,"A(end)0")==0)
				{
					difference = clock()-start;
					str1 += sprintf(str1,"Time: %3d.%03d, OS: Process %d set in Exit State\n",difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000,
						loopThroughProcesses-1);
					command = process[loopThroughCommands++];
				}
				else if(command[0] == 'O' || command[0] == 'I' || command[0] == 'P')
				{
					char* stringToPrint = cut_string_after_char(command, ')');
					difference = clock()-start;
					str1 += sprintf(str1,"Time: %3d.%03d, Process %d, %s start\n",difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000,
						loopThroughProcesses-1,stringToPrint);
					//printf("%d * %d = ", atoi(get_string_after_char(command, ')')), get_config_cycle(command[0],storedConfigData));
					run_command(command, atoi(get_string_after_char(command, ')'))*
						get_config_cycle(command[0],storedConfigData));
					difference = clock()-start;
					str1 += sprintf(str1,"Time: %3d.%03d, Process %d, %s end\n",difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000,
						loopThroughProcesses-1,stringToPrint);
					command = process[loopThroughCommands++];
				}
				else
				{
					char* stringToPrint = cut_string_after_char(command, ')');
					run_command(command, atoi(get_string_after_char(command, ')'))*
						get_config_cycle(command[0],storedConfigData));
					difference = clock()-start;
					str1 += sprintf(str1,"Time: %3d.%03d, Process %d, %s\n",difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000,
						loopThroughProcesses-1,stringToPrint);
					command = process[loopThroughCommands++];
				}
			}
			PCBstate = 3; //exit state
		}
		else{
			loopThroughProcesses++;
		}
	}
	
	difference = clock()-start;
	str1 += sprintf(str1,"Time: %3d.%03d, System stop\n\n\n", difference/CLOCKS_PER_SEC,(difference*1000)/CLOCKS_PER_SEC%1000);
	simLog[logIndex++] = holdRunString;
	simLog[logIndex++] = "End Simulation\n==========================\n\n\n";
	int loopThroughLog;
	char charToPrint;
	if(strcmp(get_log_to(storedConfigData),"Both") == 0 || strcmp(get_log_to(storedConfigData), "Monitor")==0)
	{
		loopThroughLog = 0;
		while(loopThroughLog < logIndex)
		{
			printf("%s",simLog[loopThroughLog++]);
		}
	}
	if(strcmp(get_log_to(storedConfigData),"Both")==0 || strcmp(get_log_to(storedConfigData),"File")==0)
	{
		loopThroughLog = 0;
		char* logToFilePath = get_log_file_path(storedConfigData);
		FILE *inFilePtr = fopen(logToFilePath, "w");
		while(loopThroughLog < logIndex)
		{
			fputs(simLog[loopThroughLog++],inFilePtr);
		}
		fclose(inFilePtr);
	}

}

char** get_process_from_metadata(char** inMetadata, int startingIndex, int endingIndex)
{
    int metadataIndex = startingIndex;
    int processArrayIndex = 0;
    char** processArray = (char**) malloc((endingIndex-startingIndex + 2)*sizeof(char*));
  	while(metadataIndex  < endingIndex)
  	{
  			//printf("%s ",inMetadata[metadataIndex]);
  			processArray[processArrayIndex++] = inMetadata[metadataIndex++];
    }
    processArray[processArrayIndex] = '\0';
    return processArray;
}

int* divide_processes_by_index(char** inMetadata){
	int numberOfProcesses = get_num_processes(inMetadata);
	int* processesArray = malloc((numberOfProcesses+1)*sizeof(int));
	int loopThroughMetadata = 0;
	int loopThroughProcesses = 0;
	char* command = inMetadata[loopThroughMetadata];
	while(loopThroughProcesses < numberOfProcesses)
	{
		if(strcmp(command, "A(end)0") == 0)
		{
			processesArray[loopThroughProcesses++] = loopThroughMetadata;
		}
		command = inMetadata[loopThroughMetadata++];
	}
	return processesArray;
	
}

int get_num_processes(char** inMetadata)
{
	int loopThroughMetadata = 0;
	int processes = 0;
	char* command = inMetadata[loopThroughMetadata];
	while(strcmp(command, "S(end)0") != 0)
	{
		if(strcmp(command, "A(end)0") == 0)
		{
			processes += 1;
		}
		command = inMetadata[loopThroughMetadata++];
	}
	return processes;
}

void set_pcbs_ready(int* inPCBs, int numberOfProcesses)
{
	int loopThroughPCBs = 0;
	while(loopThroughPCBs < numberOfProcesses)
	{
		inPCBs[loopThroughPCBs++] = 1;
	}
}


int get_config_cycle(char inLetter, char** storedConfigData)
{
	if(inLetter =='I' || inLetter == 'O')
	{
		return atoi(get_io_cycle_time(storedConfigData));
	}
	else if(inLetter == 'P'){
		return atoi(get_processor_cycle_time(storedConfigData));
	}
	else{
		return 0;
	}
}

void run_command(char* command, int timeToRun)
{
	//get time to run
	int msec = 0, i = 0, iterations = 0; /* 10ms */
    clock_t before = clock();
    do 
    {
    	for(i=0; i< 1000000; i++)
    	{

    	}
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        iterations++;
   } while ( msec < timeToRun );
}

char* get_version(char** storedConfigData)
{
	return storedConfigData[0];
}

char* get_file_path(char** storedConfigData)
{
	return storedConfigData[1];
}

char* get_cpu_scheduling_code(char** storedConfigData)
{
	return storedConfigData[2];
}

char* get_quantum_time(char** storedConfigData)
{
	return storedConfigData[3];
}

char* get_memory_available(char** storedConfigData)
{
	return storedConfigData[4];
}

char* get_processor_cycle_time(char** storedConfigData)
{
	return storedConfigData[5];
}

char* get_io_cycle_time(char** storedConfigData)
{
	return storedConfigData[6];
}

char* get_log_to(char** storedConfigData)
{
	return storedConfigData[7];
}

char* get_log_file_path(char** storedConfigData)
{
	return storedConfigData[8];
}