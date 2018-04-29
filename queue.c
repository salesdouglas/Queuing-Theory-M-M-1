#include <stdio.h>
#include <stdlib.h>

int main()
{
	int numberClient=0; //Number of clients the system will have
	int i=0;
	int quantity1=0;
	int quantity2=0;
	int busy=0; // Busy display to find some system error
	float timeArrival[100]; //Arrival process, which defines how the elements arrive at the system.
	float timeService[100]; //Process, which defines how the elements are.
	float arrivalRate=0.00; //Arrival rate of elements in the system.
	float attendanceRate=0.00; //System exit rate or average number of elements leaving the system.
	float timeMeanService=0.00; // Average time the server takes to service a client.
	float timeMeanWaitQueue=0.00; //Average time that the customer remains in the queue, waiting for the. 
	float timeMeanSystem=0.00; //Average time the customer stays in the system, waiting and being served.
	float timeMeanArrival=0.00;
	float timeQueue[100];
	float timeQueueTotal=0.00;
	float timeServiceTotal=0.00;
	float timeArrivalTotal=0;
	
	timeQueue[0] = 0; // The first element in the queue will always be answered immediately
	
	scanf("%d",&numberClient);
	
	for(i=0;i<numberClient;i++){
		scanf("%f",&timeArrival[i]);
		timeArrivalTotal = timeArrivalTotal + timeArrival[i];
		quantity2 = quantity2 + 1;
	}
	
	for(i=0;i<numberClient;i++){
		scanf("%f",&timeService[i]);
		quantity1=quantity1+1;
		timeServiceTotal = timeServiceTotal + timeService[i];
	}

	// Because we have two discrete variables in relation to time, indicating the time of arrival of a client in relation to another client 	and the time that a client waits to be serviced by the server, we must take some considerations in the logic bellow:

	//Considering that we are in client x, if the arrival time of the client (x -1) added to the time it takes in the server to be serviced 	is less than or equal to the sum of the arrival time of the client (x) and the time it takes the same delay to be met on the server, 		this indicates that the client (x) will have to wait a time t to be attended, with that the average time in the queue increases 	discreetly.
The calculation of the average time for a given customer is expressed by the variable timeQueue
	
	for(i=1;i<numberClient;i++){
		if((timeArrival[i-1]+timeArrival[i])<=(timeArrival[i-1]+timeService[i-1]))
		{
			busy = 1;	// Busy server indication
			timeQueue[i] = (timeArrival[i-1]+timeService[i-1])-(timeArrival[i]+timeArrival[i-1]);
			if(timeQueue[i]==0)
				timeQueue[i]=timeQueue[i]+1; 
		}
		else
		{
			busy=0; 	//Server not busy indication
			timeQueue[i] = 0;
		
		}		 
	}
	for(i=0;i<numberClient;i++)
		timeQueueTotal=timeQueueTotal+timeQueue[i];
	
	timeMeanWaitQueue = timeQueueTotal/quantity2;
	timeMeanService = timeServiceTotal/quantity1;
	timeMeanArrival = timeArrivalTotal/quantity2;
	attendanceRate = 1/timeMeanService;
	arrivalRate = 1/timeMeanArrival;
	timeMeanSystem = timeMeanWaitQueue+timeMeanService;
	
	printf("Taxa de chegada: %.2f clientes/s\n",arrivalRate);
	printf("Taxa de atendimento: %.1f clientes/s\n",attendanceRate);
	printf("E[tS] = %.2f s\n",timeMeanService);
	printf("E[tW] = %.2f s\n",timeMeanWaitQueue);
	printf("E[tQ] = %.2f s\n",timeMeanSystem);
	
    return 0;
}
