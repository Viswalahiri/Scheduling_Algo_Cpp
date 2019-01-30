/*
 *
 * Title:       (Preemptive) Priority Scheduling Algorithm.
 * Description: Taking processes and their priorities from the user, execute them in the Priority Scheduling procedure
                and calculate the average waiting time and the average turnaround time in a preemptive fashion.
 * Author:      Viswalahiri Swamy Hejeebu
 * LinkedIn:    https://in.linkedin.com/in/viswalahiri-hejeebu-45baa2155
 * GitHub:      https://github.com/Viswalahiri
 *
 */
 
#include <iostream>
using namespace std;
class PRIORITY
{
    //Member Functions
    public:
    //getdata() takes in all the inputs from the user in the form of n, arrival times, and burst times
    void getdata();
    //calculate() performs all calculations of completion times, turnaround times and waiting times.
    void calculate();
    //putdata() performs all print operations.
    void putdata();
    //atat_awt() calculates the average waiting time and average turnaround time.
    void atat_awt();
    //Member Variables
    private:
    //Declaring as pointer variables for further convenience.
    int *at,*bt,*cbt,*ct,*wt,*tat,*pid,*pr;
    int n;
    int elapsed_time=0;
    int idle_counter=0;
    int burst_sum=0;
    //average waiting time and average turnaround time
    float atat=0.0,awt=0.0;
};
void PRIORITY::getdata()
{
    //Enter the number of processes.
    cin>>n;
    //Allocating space for all processes according to the value of n
    at  = new int[n];
    bt  = new int[n];
    cbt = new int[n];
    ct  = new int[n];
    wt  = new int[n];
    tat = new int[n];
    pid = new int[n];
    pr  = new int[n];
    //Enter the arrival times of all the processes.
    for(int i=0;i<n;i++)
        cin>>at[i];
    //Enter the burst times of all processes.
    for(int i=0;i<n;i++)
    {
      cin>>bt[i];
      //cbt is the copy of the burst times. This will be used futher.
      cbt[i]=bt[i];
    }
    //Enter the priorities of all processes.
    for(int i=0;i<n;i++)
        cin>>pr[i];
}
void PRIORITY::calculate()
{
    //Assigning process IDs.
    //Here process ID implies the order in which the processes were entered.
    for(int i=0;i<n;i++)
      pid[i]=i+1;
    //Applying bubble sorting to both arrival times and burst times based upon arrival times.
    for(int j=0;j<n;j++)
    for(int i=0;i<n-1;i++)
    {
        if(at[i]>at[i+1])
        {
            int temp;

            temp=at[i];
            at[i]=at[i+1];
            at[i+1]=temp;

            temp=bt[i];
            bt[i]=bt[i+1];
            bt[i+1]=temp;

            temp=pid[i];
            pid[i]=pid[i+1];
            pid[i+1]=temp;
            
            temp=pr[i];
            pr[i]=pr[i+1];
            pr[i+1]=temp;
            
        }
    }
    //Steps to calculate the completion time

    //Initially, the elapsed time is not equal to the Completion time of the first process(or the process with the least arrival time.)
    //That was in the example of non-preemption, but since processes keep switching here, no guarentees can be given.
	
	
    //Creating three arrays 1.value_array and 2.index_array and 3. burst_array to save priorities, indices, and burst times respectively.
    int value_array[n];
    int index_array[n];
    int burst_array[n];
    //Declerations and initializations.
    int counter=0;
    burst_sum=0;
    int i,j;
    //calculates the sum of all the burst times
    for(i=0;i<n;i++)
    {
      burst_sum+=bt[i];
    }
    
    while(burst_sum!=0)
    {
      counter=0;
      //Placing all burst times and indices into arrays, whose arrival times are less than the elapsed time(already arrived)
      //and if the burst time of that process is not zero, i.e, the process hasn't completed yet.
      for(i=0;i<n;i++)
      {
        if(at[i]<=elapsed_time&&bt[i]!=0)
        {
	      idle_counter=0;
          value_array[counter]=pr[i];
          burst_array[counter]=bt[i];
          index_array[counter]=i;
          //Incrementing counter.
          counter++;
        }
      }
      //If counter is still 0, then processor is in idle state, and we use the idle counter to move to while loop after incrementing time.
      if(counter==0)
      {
          elapsed_time++;
          idle_counter=1;
      }
      if(idle_counter==0)
      {
      //Sorting all processes in the arrays based on their priorities.
      for(i=0;i<counter;i++)
      {
        for(j=0;j<counter-1;j++)
        {
        	//The Lower the priority number, the higher is the priority.
          if(value_array[j]>value_array[j+1])
            /*
			*High Priority number having higher priority can be represented by
          	if(value_array[j]<value_array[j+1]) 
          	int the above line of code.
		  	*/
		  {
            int temp1;
            temp1=value_array[j];
            value_array[j]=value_array[j+1];
            value_array[j+1]=temp1;
            
            temp1=burst_array[j];
            burst_array[j]=burst_array[j+1];
            burst_array[j+1]=temp1; 

            temp1=index_array[j];
            index_array[j]=index_array[j+1];
            index_array[j+1]=temp1;
          }
        }
      }
        //Elapsed time is equal to the the burst time of the most urgent (priority) in the array, i.e. the first(index 0).
        elapsed_time++;
        if(bt[index_array[0]]>0)
        {
        //Decrement burst time of most urgent (priority) if the burst time of that element is greater than 0.
        bt[index_array[0]]--;
        if(bt[index_array[0]]==0)
        {
            //After decrementing, if the burst_time is 0, then the completion time is equal to the elapsed time. 
            ct[index_array[0]]=elapsed_time;
        }
        }
        burst_sum=0;
        for(i=0;i<n;i++)
        {
          burst_sum+=bt[i];
        }
      }
    }
    //Steps to calculate the turnaround time & waiting time.
    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        //We use cbt since all burst times (bt) are 0. cbt is a copy of bt.
        wt[i]=tat[i]-cbt[i];
    }
    //Applying bubble sorting to arrival times,completion time, waiting time, priorities, turnaround time and burst times based upon original process orders.
    for(int j=0;j<n;j++)
    for(int i=0;i<n-1;i++)
    {
        if(pid[i]>pid[i+1])
        {
            int temp1;

            temp1=at[i];
            at[i]=at[i+1];
            at[i+1]=temp1;
            
            //Again, we use cbt.
            temp1=cbt[i];
            cbt[i]=cbt[i+1];
            cbt[i+1]=temp1;

            temp1=pid[i];
            pid[i]=pid[i+1];
            pid[i+1]=temp1;

            temp1=wt[i];
            wt[i]=wt[i+1];
            wt[i+1]=temp1;

            temp1=tat[i];
            tat[i]=tat[i+1];
            tat[i+1]=temp1;
                        
	    temp1=pr[i];
            pr[i]=pr[i+1];
            pr[i+1]=temp1;
        }
    }
}
void PRIORITY::putdata()
{
    cout<<"Process\t"<<"Arrival\t"<<"Priority\t"<<"Burst\t"<<"Completion\t"<<"Turn Around\t"<<"Waiting\t"<<endl;
    for(int i=0;i<n;i++)
    cout<<"P"<<"["<<pid[i]<<"]\t"<<at[i]<<"\t"<<pr[i]<<"\t\t"<<cbt[i]<<"\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    cout<<endl;
    cout<<"Average Waiting Time is "<<awt<<"ms."<<endl;
    cout<<"Average Turn Around is "<<atat<<"ms."<<endl;
}
void PRIORITY::atat_awt()
{
	int sumawt=0,sumatat=0;
	for(int i=0;i<n;i++)
	{
		sumawt+=wt[i];
		sumatat+=tat[i];
	}
	atat=sumatat/(float)n;
	awt=sumawt/(float)n;
}
//Driver Function
int main()
{
    PRIORITY obj;
    obj.getdata();
    obj.calculate();
    obj.atat_awt();
    obj.putdata();
    return 0;
}
/*________________________________________________________________________________________________________________________________
Sample Input:
-------------
3
0 1 2
10 5 2
3 2 1
Sample Output:
-------------
Process Arrival Priority        Burst   Completion      Turn Around     Waiting
P[1]    0       3               10      17              17              7
P[2]    1       2               5       8               7               2
P[3]    2       1               2       4               2               0

Average Waiting Time is 3ms.
Average Turn Around is 8.66667ms.
*/
