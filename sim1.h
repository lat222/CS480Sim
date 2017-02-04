#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE !FALSE
#define STD_STR_LEN 45

struct config {
	char* version_phase;
	char* file_path;
	char* cpu_scheduling_code;
	char* quant_cyc;
	char* mem_kb;
	char* process_cycle;
	char* io;
	char* log_to;
	char* log_fp;
};

int mdsize(char* file_name);
char** mdstore(char* file_name, int array_length);
void empty(char *var);
