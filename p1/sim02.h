#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define cpuSchedulingCodeDefault "FCFS-N"

char** store_config(char* fileName);
int move_pointer_to_config_data(char* inString, char charToMovePointerPast);
char** store_metadata(char* fileName);
char* get_string_of_file(char* fileName);
int count_char_in_string(char* inString, char charToCount);
int check_string_is_int_in_range(char* data, int lowerBound, int upperBound);
int check_metadata_file(char* metadataFilePath);
int check_cpu_scheduling_code(char* code);
int check_log_to(char* abort);
int check_log_file_path(char* fp);
char* cut_string_at_char(char* inString, char charToCutOut);
char* cut_string_after_char(char* inString, char charToCutOut);
char* concat(char *s1, char *s2);
char** put_metadata_in_array(char* inString, int totalProcesses);
char** put_config_in_array(char* inString);
int check_metadata_is_acceptable(char* data);
int check_program_start_and_end(char* data);
int check_process_start_and_end(char* data);


void sim02(char** storedConfigData, char** storedMetadata);
char* get_version(char** storedConfigData);
char* get_file_path(char** storedConfigData);
char* get_cpu_scheduling_code(char** storedConfigData);
char* get_quantum_time(char** storedConfigData);
char* get_memory_available(char** storedConfigData);
char* get_processor_cycle_time(char** storedConfigData);
char* get_io_cycle_time(char** storedConfigData);
char* get_log_to(char** storedConfigData);
char* get_log_file_path(char** storedConfigData);

typedef struct {
	int state;
	char** process;
} ProcessControlBlock;

void change_to_new_state(ProcessControlBlock *pcb, char**  inProcess);
void change_to_ready_state(ProcessControlBlock *pcb);
void change_to_run_state(ProcessControlBlock *pcb);
void change_to_exit_state(ProcessControlBlock *pcb);
int get_state(ProcessControlBlock *pcb);
char** get_process(ProcessControlBlock *pcb);