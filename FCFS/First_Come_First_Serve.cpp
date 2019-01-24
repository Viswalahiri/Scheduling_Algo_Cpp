/*
 * 
 * Title:       First Come First Serve Algorithm.
 * Description: Taking processes from the user, execute them in first come first serve procedure 
                and calculate the average waiting time and the average turnaround time.
 * Author:      Viswalahiri Swamy Hejeebu
 * GitHub:      https://github.com/Viswalahiri
 * LinkedIn:    https://in.linkedin.com/in/viswalahiri-hejeebu-45baa2155
 *  
 */
 
#include <iostream>
using namespace std;
class FCFS
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
    int *at,*bt,*ct,*wt,*tat,*pid;
    int n;
    //average waiting time and average turnaround time
    float atat=0.0,awt=0.0;
};
void FCFS::getdata()
{
    //Enter the number of processes.
    cin>>n;
    //Allocating space for all processes according to the value of n
    at  = new int[n];
    bt  = new int[n];
    ct  = new int[n];
    wt  = new int[n];
    tat = new int[n];
    pid = new int[n];
    //Enter the arrival times of all the processes.
    for(int i=0;i<n;i++)
        cin>>at[i];
    //Enter the burst times of all processes.
    for(int i=0;i<n;i++)
        cin>>bt[i];
}
void FCFS::calculate()
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
        }
    }
    //Steps to calculate the completion time
    
    //Completion time of process with least arrival time is sum of arrival time and burst time.
    ct[0]=at[0]+bt[0];
    for(int i=1;i<n;i++)
    {
    //if arrival time of process is greater than burst time of preceeding process, then add the difference to the completion time expression.
        if(at[i]>bt[i-1])
        ct[i]=ct[i-1]+bt[i]+(at[i]-bt[i-1]);
    //if arrival time of process is less than burst time of the preceeding process, then completion time remains the same.
        else
        ct[i]=ct[i-1]+bt[i];
    }
    //Steps to calculate the turnaround time & waiting time.
    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    
    //Applying bubble sorting to arrival times,completion time, waiting time, turnaround time and burst times based upon original process orders.
    for(int j=0;j<n;j++)
    for(int i=0;i<n-1;i++)
    {
        if(pid[i]>pid[i+1])
        {
            int temp1;
            
            temp1=at[i];
            at[i]=at[i+1];
            at[i+1]=temp1;
            
            temp1=bt[i];
            bt[i]=bt[i+1];
            bt[i+1]=temp1;
            
            temp1=pid[i];
            pid[i]=pid[i+1];
            pid[i+1]=temp1;
            
            temp1=wt[i];
            wt[i]=wt[i+1];
            wt[i+1]=temp1;
            
            temp1=tat[i];
            tat[i]=tat[i+1];
            tat[i+1]=temp1;
        }
    }
}

void FCFS::putdata()
{
    cout<<"Process\t"<<"Arrival\t"<<"Burst\t"<<"Completion\t"<<"Turn Around\t"<<"Waiting\t"<<endl;
    for(int i=0;i<n;i++)
    cout<<"P"<<"["<<pid[i]<<"]\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    cout<<endl;
    cout<<"Average Waiting Time is "<<awt<<"ms."<<endl;
    cout<<"Average Turn Around is "<<atat<<"ms."<<endl;
}

void FCFS::atat_awt()
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
    FCFS obj;
    obj.getdata();
    obj.calculate();
    obj.atat_awt();
    obj.putdata();
    return 0;
}
_________________________________________________________________________________________________________________________________
Sample Input: 
-------------
5
0 1 2 3 4
10 5 20 15 5

Sample Output:
-------------
Process Arrival Burst   Completion      Turn Around     Waiting
P[1]    0       10      10              10              0
P[2]    1       5       15              14              9
P[3]    2       20      35              33              13
P[4]    3       15      50              47              32
P[5]    4       5       55              51              46

Average Waiting Time is 20ms.
Average Turn Around is 31ms.
