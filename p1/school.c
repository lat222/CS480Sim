#include "read_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int i, j, check;
char buffer[100];
char mdata_buff[100];
int loop, mdata_loop;
int mdata_count = 0;
int getloop = 0;
struct mdatas mdata_struct[50];

//helper function
void skip_to_next(FILE* config)
{
  loop = fgetc(config);
  while(loop != ':')
  {
    loop = fgetc(config);
  }
  loop = fgetc(config);
}



void  read_mdata(FILE* mdata)
{
  //allocate space for an array of mdata

  
  //skip first line
  fgets(buffer, 50, mdata);
  
  while (mdata_loop != '.')
  {
    
    
    //take in one letter action 
    mdata_loop = fgetc(mdata);
    
    
    //check to see if we've hit the end of the line on mdata
    if(mdata_loop == '\n')
    {
      
      mdata_loop = fgetc(mdata);
      while(isspace(mdata_loop))
      {
        mdata_loop = fgetc(mdata);
      }
    }
    
    //save to action
    mdata_struct[mdata_count].action = mdata_loop;
  
    
    //check for error in file
    if (mdata_loop = fgetc(mdata) != '(') return;
    
    
    getloop = 0;
    while(mdata_loop != ')')
    {
      //loops through operator and inputs operator letter by letter 
      
      mdata_struct[mdata_count].oper[getloop] = mdata_loop;
      
      mdata_loop = fgetc(mdata);
      getloop += 1;
      
      
    }
    
  
    //put string ending at the end 
    mdata_struct[mdata_count].oper[getloop] = '\0';
    getloop = 0;
    
    //now store cycle time or mem
    
      mdata_loop = fgetc(mdata);
    while(mdata_loop != ';')
    {
      
      mdata_struct[mdata_count].cycle_time[getloop] = mdata_loop;
      
      mdata_loop = fgetc(mdata);
      
      if(mdata_loop == '.') break;
      getloop += 1;
      
    }   
    mdata_struct[mdata_count].cycle_time[getloop] = '\0';
    
    getloop = 0;
    
    
    check = fgetc(mdata);
  
    
    mdata_count += 1;
    

  }
  
  fclose(mdata);
  i = mdata_count;
  
  
  
  
}

//method to read in config file and store to struct
struct configs read_config(FILE* config)
{
  struct configs config1;
  
  //first pass through first line
  fgets(buffer, 50, config);
  
  skip_to_next(config);
  
  
  //read in value
  fgets(config1.version, 50, config);
  
  
  //read in test file
  skip_to_next(config);
  
  fgets(config1.file, 50, config);
  
  skip_to_next(config);
  
  fgets(config1.cpu_sched, 50, config);
  
  //change none to cpu_sched type
  if(strcmp(config1.cpu_sched, "NONE"))
  {
    strncpy(config1.cpu_sched, "FCFS_N\n", 50);
  }
  
  skip_to_next(config);
  
  //store cycles
  fgets(config1.cycles, 50, config);
  
  skip_to_next(config);
  
  //store memory
  fgets(config1.memory, 50, config);
  
  
  skip_to_next(config);
  
  //store cycle time
  fgets(config1.p_cycle_time, 50, config);
  
  skip_to_next(config);
  
  //store io cycle time
  fgets(config1.io_cycle_time, 50, config);
  
  skip_to_next(config);
  
  fgets(config1.log_to, 50, config);
  
  skip_to_next(config);
  
  fgets(config1.log_file_path, 50, config);
  
  fclose(config);
  
  return config1;
  

}

int main(int argc, char *argv[])
{
  
  FILE* config = fopen(argv[1], "r");
  
  struct configs to_print;
  to_print = read_config(config);
  FILE* mdata = fopen("testfile.mdf", "r");
  read_mdata(mdata);
  
  printf("Configuration is as follows: \n");
  printf("Version: %s \n", to_print.version);
  printf("File: %s \n", to_print.file);
  printf("Cpu Sched Time: %s \n", to_print.cpu_sched);
  printf("Cycles: %s \n", to_print.cycles);
  printf("Memory: %s \n", to_print.memory);
  printf("Processor Cycle Time: %s \n", to_print.p_cycle_time);
  printf("IO Cycle Time: %s \n", to_print.io_cycle_time);
  printf("log to: %s \n", to_print.log_to);
  printf("Log file path: %s \n", to_print.log_file_path);
  printf("\n");
  
  
  printf("Mdata operations are as follows: \n");
  for ( j = 0; j < i; j++)
  {
    printf("Instruction set %d: \n", j);
    printf("\n");
    printf("Command: %c \n", mdata_struct[j].action);
    printf("Operator: %s\n", mdata_struct[j].oper);
    printf("Cycle time: %s \n", mdata_struct[j].cycle_time);
    printf("\n");
  }
  
  
  
  
  
}