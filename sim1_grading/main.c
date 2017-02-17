#include<stdio.h>
#include<string.h>
#include"myQueue.h"
#include"myMethods.h"

 

int main(int argc, char* argv[]) {
	
	delimitMD();
    delimitConfig();
    checkEmpty();
    printf("------------------------\n");
    removeInt();
    Display();
    printf("------------------------\n");
     printf("Front = %d", front);
     front = 73;
     printf("Front = %d", front);
     addInt(99);
     addInt(22);
     int i = 0;
     int queueItem;
     while((queueItem = removeInt()) != 0){
     	printf("Queue item %d: %d\n", i++, queueItem);
     }
    return 0;
    //displayArray;
   
}