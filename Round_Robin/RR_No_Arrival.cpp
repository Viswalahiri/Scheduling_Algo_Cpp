#include<iostream>
using namespace std;
class Round
{
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
	public:
		void getdata();
        	void calculator();
        	void tat_wt();
        	void atat_awt();
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
		//Getting the copy of the 
		cbt[i]=bt[i];
        }
	//Initalizing arrival times and completion times as 0.
        for (i=0;i<n;i++)
        {
        at[i]=0;
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
			//Doubtful
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
		tat[i]=ct[i];
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
/*________________________________________________________________________________________________________________________________
Sample Input:
-------------
Enter the number of processes.
3
Enter the time quantum.
5
Enter the burst times of 3 processes.
30 6 8
Sample Output:
-------------
Process Arrival Burst   Completion      Turn Around     Waiting
P[1]    0       30      44              44              14
P[2]    0       6       21              21              15
P[3]    0       8       24              24              16

Average Waiting Time is 15ms.
Average Turn Around is 29.6667ms.
*/                            
