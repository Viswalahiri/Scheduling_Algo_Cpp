/*
 * 
 * Title:       Round Robin algorithm with arrival time.
 * Description: Taking processes from the user, execute them in round robin fashion
                and calculate the average waiting time and the average turnaround time.
 * Author:      Puja Kumari
 * GitHub:      https://github.com/pujakumari19
 * LinkedIn:    https://www.linkedin.com/in/puja-kumari-15732a192/
 *  
 */

#include<iostream>
using namespace std;
class Round
{
	//Member Variables
        private:
                int i,j,k;
                float atat=0.0,awt=0.0;
                int elapsed_time=0;
                int burst_sum=0;
                int n,t_q;
                int *pno;
                int *at;
                int *bt;
                int *cbt;
                int *ct;
                int *tat;
                int *wt;
	//Member Functions
	public:
	//getdata() takes in all the inputs from the user in the form of n, arrival times, and burst times
		void getdata();
	//calculate() performs all calculations of completion times.
        	void calculator();
	 //tat_wt() calculates the waiting times and turnaround times.
        	void tat_wt();
	 //atat_awt() calculates the average waiting time and average turnaround time.
        	void atat_awt();
	//putdata() performs all print operations.
       		void putdata();
};
void Round::getdata()
{
        cout<<"Enter the number of processes."<<endl;
        cin>>n;
        cout<<"Enter the time quantum."<<endl;
        cin>>t_q;
        pno=new int[n+1];
        at=new int[n+1];
        bt=new int[n+1];
	//cbt is a copy of the original burst times. This will be used later in the program as bt changes throughout the program.
        cbt=new int[n+1];
        ct=new int[n+1];
        tat=new int[n+1];
        wt=new int[n+1];
        cout<<"Enter the burst times of "<<n<<" processes."<<endl;

        for (i=0;i<n;i++)
        {
        	cin>>bt[i];
        	burst_sum+=bt[i];
		//Getting the copy of the burst times
		cbt[i]=bt[i];
        }
        cout<<"Enter the arrival times of "<<n<<" processes."<<endl;
	//Initalizing arrival times and completion times as 0.
        for (i=0;i<n;i++)
        {
        //at[i]=0;
        cin>>at[i];
        }
        for (i=0;i<n;i++)
        {
        ct[i]=0;
        }
}
void Round::calculator()
{
	//Loop will repeat as long as burst sum is more than 0, i.e, a process remains unfinished.
        while(burst_sum>0)
        {
        for(i=0;i<n;i++)
        {
		//If time quantum is more or equal to the present burst time of certain process, then...
                if(bt[i]<=t_q)
                {
			//elapsed time adds itself to the 'then' burst time.
                        elapsed_time+=bt[i];
			//burst time becomes 0
                        bt[i]=0;
                        
                        if(ct[i]==0)
                        {
                        ct[i]=elapsed_time;
                        }
                }
		//If time quantum is less than the burst time of that certain process...
                else
                {
		//burst time of that process subtracts the time quantum from itself
                bt[i]-=t_q;
		//elapsed time is increased by time quantum.
                elapsed_time+=t_q;
                }
        }
	//Recalculating burst sum for the while loop condition.
        burst_sum=0;
        for (i=0;i<n;i++)
        {
                burst_sum+=bt[i];
        }

        }
}
void Round::tat_wt()
{
	//Formula for Turn-Around time and waiting time.
        for(i=0;i<n;i++)
        { 
		tat[i]=ct[i]-at[i];
                wt[i]=tat[i]-cbt[i];
        }
}

void Round::atat_awt()
{
        int sumatat=0;
        int sumawt=0;
        for(i=0;i<n;i++)
        {
                sumatat+=tat[i];
                sumawt+=wt[i];
        }
        atat=sumatat/float(n);
        awt=sumawt/float(n);
}
void Round::putdata()
{
    cout<<"Process\t"<<"Arrival\t"<<"Burst\t"<<"Completion\t"<<"Turn Around\t"<<"Waiting\t"<<endl;
    for(int i=0;i<n;i++)
    cout<<"P"<<"["<<i+1<<"]\t"<<at[i]<<"\t"<<cbt[i]<<"\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    cout<<endl;
    cout<<"Average Waiting Time is "<<awt<<"ms."<<endl;
    cout<<"Average Turn Around is "<<atat<<"ms."<<endl;
}

int main()
{
        Round obj;
        obj.getdata();
        obj.calculator();
        obj.tat_wt();
        obj.atat_awt();
        obj.putdata();
        return 0;
}
