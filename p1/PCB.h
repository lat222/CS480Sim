#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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