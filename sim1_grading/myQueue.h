// DISCLAIMER: This code was derived/ based off the code available at GeeksforGeeks.com. There version of the queue off the array is much like this none, not using a rear variable being very noticable 

#define MAX 100000
//#define NULL 0


int myQueue[MAX];
int front;
int myIndex;
int length;

// This method displays the index of the queue. i.e. This method allows the user to know where the "pointer" is.
void Display()
{
	printf("%d\n", myQueue[myIndex]);
	myIndex = (myIndex + 1);
}

//This adds an integer value to the queue. I incremented the myNum value so that we can theoretically move the front of the queue without actually having to
void addInt(int num)
{
	int myNum = front;
	while(myQueue[myNum] != 0)
	{
		myNum++;
	}
	length = length +1;
	myQueue[myNum] = num;

}

	
//This just takes the value out of the front of the queue and moves the front forward, creating a new front value
int removeInt()
{
	int temp = myQueue[front];
	myQueue[front] = 0;
	
	
	front++;
	myIndex = front;
	return temp;
}




// This method loops through the array, printing every value from it as it goes through, ending at the last value in the queue.
void displayArray()
{
	while(front < length)
	{
		printf("%d\n", myQueue[front]);
		front++;
	}	
}

//checks if the queue is full and sends the user a message if it is
void checkFull()
{
	if (length == MAX)
	{
		printf("Your Queue is full\n");
	}
	else
	{
		printf("Your queue is NOT full");
	}
	
}


//Checks the queue to see if there a value in the front, where a value must be if the queue is not empty.
void checkEmpty()
{
	int myNum = front;
	if(myQueue[myNum] < 1)
	{
		printf("The Queue is empty\n");
	}

	
else if(length == 100000)
{
	printf("The Queue is full\n");
}
	
	else 
		{
			printf("The Queue is not empty\n");	
		}
}






