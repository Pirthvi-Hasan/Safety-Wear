#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>

double num[8]={1111111111,2222222222,3333333333,4444444444};            // Mobile Numbers of Users Relatives or Friends recieved from the user....

float steps,acc,v,d,tm,lat,lng;
int zoom,hrt_rte;

double stop_watch()							//   Stop Watch feature as in all other watches....
{
	double time=0;
	char opt;
	
	//  Begins the stop_watch...
	clock_t begin = clock();                       
	
	printf("\n\nPress a key to stop : ");
	opt=getch();
	
	//  Stops the stop_watch...
	clock_t end = clock();                            
	
	//  Calculates the time difference...
	time+=(double)(end-begin)/CLOCKS_PER_SEC;      
	
	return time;
}

void timer()								// Timer feature as in all other watches....
{
	float stop,t=0;
	char opt;
	clock_t begin,end;
	
	printf("\n\nEnter a time : ");
	scanf("%f",&stop);
	printf("\n");
	
	//  Begins the timer...
	begin = clock();                       
	
	while(t<stop)
	{
		//  Stops the timer...
		end = clock();        
		             
		t=(float)(end-begin)/CLOCKS_PER_SEC;
		printf("\b\b\b\b\b\b%.2f",t);   
	}
	
	printf("\b\b\b\b\b\b%.2f\a",stop);
	printf("\n\nTime\'s Up !!");
	
}

void gps_sen()								//  function for GPS sensor....
{
	//  Gets the  latitude from GPS...
	lat=39.774769;       
	
	//  Gets the longitude from GPS...
	lng=-74.860840;     
	
	//  Zooms the map by 'x' times...
	zoom=15;           
}

int ppg_sen()								//  function for PPG (heartbeat) sensor....
{
	int i=0;
	int ppg=srand()%116;
	
	//  Calculates the Heart_Rate value...
	while(ppg<36)
	ppg=rand()%116;
	
	printf("HEART RATE : %d\n\n",ppg);
	
	return ppg;
}
 
void acceler()								//  function for tracking distance....
{
	int i=0;
	acc=srand()%10;
	tm=srand()%120;	
	
	//  Calculate the acceleration...
	while(acc<1)
	acc=rand()%10;
	acc/=10;
	
	//  Calculate the time duration...
	while(tm<60)
	tm=rand()%120;
	
	//  Calculate the Veloctiy...
	v=acc*tm;  
	
	//  Calculate the Distance...
	d=v*tm;    
	
	//  Calculate the Steps_Taken...
	steps=d*1.312;   
	
	printf("\n---WALK DETAILS---\n\n");
	printf("DURATION     : %-9.2f sec  \n\n",tm);
	printf("ACCELERATION : %-9.2f m/s^2\n\n",acc);
	printf("VELOCITY     : %-9.2f m/s  \n\n",v);
	printf("DISTANCE     : %-9.2f mts  \n\n",d);
	printf("STEPS TAKEN  : %-9.2f stps\n",steps);
	
}

void vibrate()
{
	//  Gives a Vibration_Alert...
	printf("\a");        
}

void message()								// function to send distress_messages to friends and relatives....
{
	int i; 
	
	//  Sends the following message to the numbers given by User...
		
	printf("\n\n\n        \" Your Friend/Relative may be stuck in some problem!");
	printf("\n\n          Please check whether they\'re Safe !!");
	printf("\n\n          Click on the below link for their location !!!");
	
	//  Link to access the user's location...
	printf("\n\n          Location : https:\\www.google.com/maps/@%f,%f,%dz \"\n\n",lat,lng,zoom);    
	
	for(i=0;i<8;i++)
	{
	printf("\nMessage sent to : %.0lf",num[i]);
	}
	printf("\n");
	
}

main()
{
	
	FILE *ptr;
	double tme;
	int ppg;
	
	char opt,file[30]="Rodeo.txt",ext[5]="a+";
	
	time_t t;
	time(&t);

	printf("\n\n                                         -x-x-  RODEO_WATCHES  -x-x-");
	printf("\n\n                                    DATE & TIME : %s \n\n",ctime(&t));
	
	//  Gets position vector values from gps_sensor
	gps_sen();               
	
	//  Gets the heart-rate values from ppg_sensor                                                                           
	ppg=ppg_sen();           
	
	//  Gets the acceleration of user from accelerometer
	acceler();               
	
	//  Additional Features in a Fitness_Watch ( Stop_Watch / Timer ) ...
	
	printf("\n\n1.Stop_Watch\n\n2.Timer\n\n\nEnter your option : ");
	opt=getche();
	
	if(opt=='1')
	{
	    //  Stop_Watch...
	    
		tme=stop_watch();
		printf("\n\nTime elapsed : %.2f sec\n",tme);
	}
	
	if(opt=='2')
	{
		//  Timer...
		
		timer();
	}
	
	//  User is Good and Relaxed...  :-|
	
	if(ppg<60)                 
	{
		printf("\n\n\n-----STATUS-----\n");
		printf("\nYou are so calm and Relaxed!!!");
		printf("\nTime to do some work...\n");
	}
	
	//   User is Healthy and active... :-)
	
	else if(ppg>59&&ppg<90)
	{
		printf("\n\n-----STATUS-----\n");
		printf("\nYou\'re maintaining a Good Health !\nKeep it up !!\n");
	}
	
	//  User is in fear and in distress...  :-(
	
	else
	{
		vibrate();
		message();
	}
	
	//  Open the File to store the user Data...
	if((ptr=fopen(file,ext))==NULL)
	printf("\nCannot open file...!");
	
	else 
	{
		//  Stores the generated Data in a File ( Each time while being recorded ) ...
		
		fprintf(ptr,"\n\nDATE & TIME  : %s",ctime(&t));
		
		fprintf(ptr,"HEART RATE   : %d",ppg);
		fprintf(ptr,"\nDURATION     : %-9.2f sec  ",tm);
		fprintf(ptr,"\nACCELERATION : %-9.2f m/s^2",acc);
		fprintf(ptr,"\nVELOCITY     : %-9.2f m/s  ",v);
		fprintf(ptr,"\nDISTANCE     : %-9.2f mts  ",d);
		fprintf(ptr,"\nSTEPS TAKEN  : %-9.2f stps ",steps);
	}	
}
