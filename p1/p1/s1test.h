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
char** put_metadata_in_array(char* inString, int totalProcesses);
int check_metadata_is_acceptable(char* data);
int check_program_start_and_end(char* data);
int check_process_start_and_end(char* data);
