#include "PCB.h"

int main(int argc, char* argv[]){
	// read in metadata file
	char** processes = (char *[]) {"These", "are", "some", "strings"};
	ProcessControlBlock *x;
	change_to_new_state(x,processes);
	change_to_ready_state(x);
	printf("%d",get_state(x));

}


void change_to_new_state(ProcessControlBlock *pcb, char** inProcess)
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
char** get_process(ProcessControlBlock *pcb)
{
	return (char**) pcb->process;
}