#include "PCB.h"

int main(int argc, char* argv[]){
	// read in metadata file
	char* processes = malloc(11*5*sizeof(char));
	char** toPrint = (char*[]) {"hello", "there", "wass", "up","hella","right","back" "there", "wazz", "p"};
	int i = 0;
	while(i<9){
		char* command = toPrint[i++];
		int j = 0;
		while(j<(sizeof(command)/sizeof(char)))
		{
			printf("%c", command[j]);
			processes[j] = command[j++];
		}
		printf(" ");
	}
	printf("\n");
	ProcessControlBlock *x;
	change_to_new_state(x,processes);
	change_to_ready_state(x);
	printf("%s",get_process(x));

}


void change_to_new_state(ProcessControlBlock *pcb, char* inProcess)
{
	pcb->state = 0;
	pcb->process = inProcess;
}
void change_to_ready_state(ProcessControlBlock *pcb)
{
	pcb->state = 1;
}
void change_to_run_state(ProcessControlBlock *pcb)
{
	pcb->state = 2;
}
void change_to_exit_state(ProcessControlBlock *pcb)
{
	pcb->state = 3;
}
int get_state(ProcessControlBlock *pcb)
{
	return (int) pcb->state;
}
char* get_process(ProcessControlBlock *pcb)
{
	return (char*) pcb->process;
}